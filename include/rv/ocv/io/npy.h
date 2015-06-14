#ifndef RV_IO_NPY_H
#define RV_IO_NPY_H

//Based on https://github.com/rogersce/cnpy

#include <cstdlib>
#include <cstdio>
#include <sstream>

#include <opencv2/core/core.hpp>

#include <boost/filesystem.hpp>
#include <boost/shared_array.hpp>

#include <rv/log/log.h>


namespace rv {
namespace io {
  

//TODO: remove asserts
template <typename Dtype>
inline cv::Mat_<Dtype> ReadNpy(const boost::filesystem::path& path) {
  FILE* fp = fopen(path.c_str(), "rb");
  if(!fp) {
    LOG_ERROR << "could not open file in ReadNpy";
  }
  
  //load header
  char buffer[256];
  size_t res = fread(buffer,sizeof(char),11,fp);       
  if(res != 11) {
    LOG_ERROR << "parse_npy_header: failed fread";
  }
  std::string header = fgets(buffer,256,fp);
  assert(header[header.size()-1] == '\n');

  //fortran order
  int loc1 = header.find("fortran_order")+16;
  bool fortran_order = (header.substr(loc1,5) == "True" ? true : false);

  //shape
  loc1 = header.find("(");
  int loc2 = header.find(")");
  std::string str_shape = header.substr(loc1 + 1, loc2 - loc1 - 1);
  unsigned int ndims = 0;
  if(str_shape[str_shape.size()-1] == ',') {
    ndims = 1;
  }
  else {
    ndims = std::count(str_shape.begin(),str_shape.end(),',')+1;
  }
  
  boost::shared_array<unsigned int> shape(new unsigned int[ndims]);
  for(unsigned int i = 0;i < ndims;i++) {
    loc1 = str_shape.find(",");
    shape[i] = atoi(str_shape.substr(0,loc1).c_str());
    str_shape = str_shape.substr(loc1+1);
  }

  //endian, word size, data type
  //byte order code | stands for not applicable. 
  //not sure when this applies except for byte array
  loc1 = header.find("descr")+9;
  bool littleEndian = (header[loc1] == '<' || header[loc1] == '|' ? true : false);
  assert(littleEndian);

  char type = header[loc1+1];
  assert(type == map_type(T));

  std::string str_ws = header.substr(loc1+2);
  loc2 = str_ws.find("'");
  unsigned int word_size = atoi(str_ws.substr(0,loc2).c_str());
  
//   std::cout << "ndims: " << ndims << std::endl;
//   std::cout << "type: " << type << std::endl;
//   std::cout << "ws: " << word_size << std::endl;
  
  
  //compute size
  unsigned long long size = 1; 
  for(unsigned int i = 0;i < ndims;i++) {
    size *= shape[i];
  }
  
  //read the data
  boost::shared_array<char> data(new char[size * word_size]);
  size_t nread = fread(data.get(), word_size, size, fp);
  if(nread != size) {
    LOG_ERROR << "load_the_npy_file: failed fread";
  }
  
  fclose(fp);
  
  
  //convert to opencv mat
  int rows, cols;
  if(ndims == 1) {
    rows = shape[0];
    cols = 1;
  }
  else if(ndims == 2) {
    rows = shape[0];
    cols = shape[1];
  }
  else {
    LOG_ERROR << "ReadNpy ndims != 1 or 2";
  }
  
  cv::Mat_<Dtype> mat(rows, cols);
  int data_idx = 0;
  for(int row = 0; row < mat.rows; ++row) {
    for(int col = 0; col < mat.cols; ++col) {
      
      if(type == 'i' && word_size == 4) {
        mat(row, col) = (reinterpret_cast<int32_t*>(data.get()))[data_idx];
      }
      else if(type == 'i' && word_size == 8) {
        mat(row, col) = (reinterpret_cast<int64_t*>(data.get()))[data_idx];
      }
      else if(type == 'u' && word_size == 4) {
        mat(row, col) = (reinterpret_cast<uint32_t*>(data.get()))[data_idx];
      }
      else if(type == 'u' && word_size == 8) {
        mat(row, col) = (reinterpret_cast<uint64_t*>(data.get()))[data_idx];
      }
      else if(type == 'f' && word_size == 4) {
        mat(row, col) = (reinterpret_cast<float*>(data.get()))[data_idx];
      }
      else if(type == 'f' && word_size == 8) {
        mat(row, col) = (reinterpret_cast<double*>(data.get()))[data_idx];
      }
      else if(type == 'b' && word_size == 1) {
        mat(row, col) = (reinterpret_cast<bool*>(data.get()))[data_idx];
      }
      else {
        LOG_ERROR << "unknown type/word_size";
      }
      
      data_idx++;
    }
  }
  
  return mat;
}


template <typename Dtype>
inline void WriteNpy(const boost::filesystem::path& path, const cv::Mat_<Dtype>& mat) {
  FILE* fp = fopen(path.c_str(), "wb");
  
  std::stringstream ss_dict;
  //write dict
  ss_dict << "{'descr': '";
  
  //  big endian test 
  unsigned char x[] = {1,0};
  short y = *(short*) x;
  char endian = y == 1 ? '<' : '>';
  ss_dict << endian;
  
  //  data type
  if(typeid(Dtype) == typeid(int32_t) || typeid(Dtype) == typeid(int64_t)) {
    ss_dict << 'i';
  }
  else if(typeid(Dtype) == typeid(uint32_t) || typeid(Dtype) == typeid(uint64_t)) {
    ss_dict << 'u';
  }
  else if(typeid(Dtype) == typeid(float) || typeid(Dtype) == typeid(double)) {
    ss_dict << 'f';
  }
  else if(typeid(Dtype) == typeid(bool)) {
    ss_dict << 'b';
  }
  else {
    LOG_ERROR << "unknown dtype for WriteNpy";
  }
  ss_dict << sizeof(Dtype);
  
  //  shape
  ss_dict << "', 'fortran_order': False, 'shape': (" << mat.rows << ", " << mat.cols << "), }";
  
  std::string dict_str = ss_dict.str();
  while((dict_str.size() + 10) % 16 != 15) {
    dict_str += " ";
  }
  dict_str += "\n";
  
  //create header str 
  std::stringstream ss_header;
  ss_header << ((char) 0x93) << "NUMPY" << ((char) 0x01) << ((char) 0x00);
  unsigned short dict_size = dict_str.size();
  ss_header << ( *((char*) &dict_size + 0) ) << ( *((char*) &dict_size + 1) );
  
  std::string header_str = ss_header.str() + dict_str;
  
//   std::cout << "======= header string ===========" << std::endl;
//   std::cout << header_str << std::endl;
//   std::cout << "===================" << std::endl;
  
  //write header to file
  const char* header = header_str.c_str();
  fwrite(header, sizeof(char), header_str.size(), fp);
  
  //write content to file 
  fwrite(mat.data, sizeof(Dtype), mat.rows * mat.cols, fp);
  
  fclose(fp);
}

  
}
}

#endif