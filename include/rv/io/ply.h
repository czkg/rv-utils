#ifndef RV_IO_PLY_H
#define RV_IO_PLY_H

#include <fstream>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <opencv2/core/core.hpp>


namespace rv {
namespace cv {

  
template <typename T>
inline cv::Mat_<T> ReadPly(std::string plyfile, bool homogenous) {
  cv::Mat_<T> points;
  
  std::ifstream label_file(plyfile.c_str());
  std::string line;
  
  bool read = false;
  int pt_idx = 0;
  int n_points = 0;
  
  while(std::getline(label_file, line)) {
    std::istringstream iss(line);
    std::string token;
    
    if(read) {            
      iss >> points(0, pt_idx);
      iss >> points(1, pt_idx);
      iss >> points(2, pt_idx);
      points(3, pt_idx) = 1;
      
      pt_idx++;
    }
    else {
      boost::algorithm::trim(line);
      if(line == "end_header") {
        read = true;
        points = cv::Mat_<T>(4, n_points);
      }
      
      iss >> token;
      if(token == "element") {
        iss >> token;
        if(token == "vertex") {
          iss >> n_points;
        }
      }
    }
  }
  
  if(!homogenous) {
    points = points.rowRange(0, 4);
  }
  
  return points;
}


inline void WritePly(const std::string plyfile, const std::vector<cv::Vec3f>& pts, const std::vector<cv::Vec3f>& clrs) {
  std::ofstream out(plyfile.c_str());
  
  //header
  out << "ply" << std::endl;
  out << "format ascii 1.0" << std::endl;
  out << "element vertex " << pts.size() << std::endl;
  out << "property float x" << std::endl;
  out << "property float y" << std::endl;
  out << "property float z" << std::endl;
  out << "property uchar red" << std::endl;
  out << "property uchar green" << std::endl;
  out << "property uchar blue" << std::endl;
  out << "end_header" << std::endl;
  
  //data
  for(size_t idx = 0; idx < pts.size(); ++idx) {
    out << pts[idx](0) << " "
        << pts[idx](1) << " "
        << pts[idx](2) << " "
        << int(clrs[idx](0)) << " "
        << int(clrs[idx](1)) << " "
        << int(clrs[idx](2)) << std::endl;
  }
  
  out.close();
}
    
    
} //ns cv
} //ns rv

#endif
