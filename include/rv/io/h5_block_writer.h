#ifndef RV_IO_H5_BLOCK_WRITER_H
#define RV_IO_H5_BLOCK_WRITER_H

#include <iostream>
#include <fstream>

#include "hdf5.h"
#include "hdf5_hl.h"

#include <opencv2/core/core.hpp>

#include <boost/format.hpp>

#include <rv/log/log.h>


namespace rv {
namespace io {

template <typename Dtype>
class H5BlockWriter {
public:
  H5BlockWriter() {}
  virtual ~H5BlockWriter() {};
  
  void init(const std::string& name, int channels, int height, int width) {
    num_[name] = 0;
    channels_[name] = channels;
    heights_[name] = height;
    widths_[name] = width;
  }
  
  void add(const std::string& name, const cv::Mat_<Dtype>& mat) {
    if(mat.rows != heights_[name] || mat.cols != widths_[name]) {
      LOG_ERROR << "mat size does not match init params";
    }
    
    for(int row = 0; row < mat.rows; ++row) {
      for(int col = 0; col < mat.cols; ++col) {
        data_[name].push_back(mat(row, col));
      }
    }
  }

  void add(const std::string& name, const Dtype& d) {
    data_[name].push_back(d);
  }
  
  size_t currentNum(const std::string& name) {
    if(data_.find(name) == data_.end()) {
      return 0;
    }
    else {
      return data_[name].size() / (channels_[name] * heights_[name] * widths_[name]);
    }
  }
  
  size_t totalNum(const std::string& name) {
    return num_[name] + currentNum(name);
  }

  herr_t createH5Dataset(hid_t file_id, const char* file_name, int rank, const hsize_t* dims, const float* buffer) {
    return H5LTmake_dataset_float(file_id, file_name, 4, dims, buffer);
  }
  
  herr_t createH5Dataset(hid_t file_id, const char* file_name, int rank, const hsize_t* dims, const double* buffer) {
    return H5LTmake_dataset_double(file_id, file_name, 4, dims, buffer);
  }
  
  void writeCurrent(const std::string& h5_path, bool is_prefix = true) {
    //list file name
    int list_idx = h5files_.size();
    
    std::string h5filename; 
    if(is_prefix)
      h5filename = boost::str( boost::format("%s%08d.h5") % h5_path % list_idx );
    else {
      h5filename = h5_path;
    }
    h5files_.push_back(h5filename);
    
    
    //write actual content
    //open hdf5
    hid_t file_id = H5Fcreate(h5filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if(file_id < 0) {
      LOG_ERROR << "Failed to open HDF5 file " << h5filename;
    }

    //save hdf5
    typename std::map<std::string, std::vector<Dtype> >::iterator it;
    for(it = data_.begin(); it != data_.end(); ++it) {
      std::string name = it->first;
      
      if(channels_.find(name) == channels_.end()) {
        LOG_ERROR << "can not write " << name << " without initialization";
      }
      
      int channels = channels_[name];
      int height = heights_[name];
      int width = widths_[name];
      int num = data_[name].size() / (channels * height * width);
      
      hsize_t dims[4];
      dims[0] = num;
      dims[1] = channels;
      dims[2] = height;
      dims[3] = width;
      
      herr_t status = -1;
      status = createH5Dataset(file_id, name.c_str(), 4, dims, &(data_[name][0]));
      if(status < 0) {
        LOG_ERROR << "Failed to make float dataset " << name;
      }
    }

    //close hdf5
    herr_t status = H5Fclose(file_id);
    if(status < 0) {
      LOG_ERROR << "Failed to close HDF5 file " << h5filename;
    }
  }
  
  void clearCurrent() {
    typename std::map<std::string, std::vector<Dtype> >::iterator it;
    for(it = data_.begin(); it != data_.end(); ++it) {
      std::string name = it->first;
      num_[name] += currentNum(name);
      data_[name].clear();
    }
  }
  
  void flushCurrent(const std::string& h5_path, bool is_prefix = true) {
    writeCurrent(h5_path, is_prefix);
    clearCurrent();
  }
  
  void writeListFile(const std::string& listfilename) {
    std::ofstream fout(listfilename.c_str());
    
    for(size_t idx = 0; idx < h5files_.size(); ++idx) {
      fout << h5files_[idx] << std::endl;
    }
        
    fout.close();
  }
    
public:  
  std::vector<std::string> h5files_;
  
  std::map<std::string, int> num_;
  std::map<std::string, int> channels_;
  std::map<std::string, int> heights_;
  std::map<std::string, int> widths_;
  
  std::map<std::string, std::vector<Dtype> > data_;
};

} //ns io
} //ns rv





#endif