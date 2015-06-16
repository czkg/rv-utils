// Copyright (C) 2015 Institute for Computer Graphics and Vision (ICG),
//   Graz University of Technology (TU GRAZ)

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the ICG, TU GRAZ.
// 4. Neither the name of the ICG, TU GRAZ nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY ICG, TU GRAZ ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ICG, TU GRAZ BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
