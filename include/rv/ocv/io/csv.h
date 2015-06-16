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

#ifndef RV_OCV_IO_CSV_H
#define RV_OCV_IO_CSV_H

#include <fstream>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <opencv2/core/core.hpp>


namespace rv {
namespace ocv {

  
template <typename T>
inline void WriteCsv(std::ostream& out, const cv::Mat_<T> mat, boost::format fmt = boost::format("% .8e")) {
  for(int row = 0; row < mat.rows; ++row) {
    for(int col = 0; col < mat.cols; ++col) {
      out << boost::str(fmt % mat(row, col));
      if(col < mat.cols - 1) {
        out << ", ";
      }
      else {
        out << std::endl;
      }
    }
  }
}


template <typename T>
inline void WriteCsv(boost::filesystem::path file, const cv::Mat_<T> mat, boost::format fmt = boost::format("% .8e")) {
  std::ofstream out(file.c_str());
  WriteCsv(out, mat, fmt);
  out.close();
}


template <typename T>
inline cv::Mat_<T> ReadCsv(boost::filesystem::path p, char delim = ',', T defaultval = 0) {
  std::ifstream file(p.c_str());
  std::vector< std::vector<std::string> > data;
  std::vector<std::string> row;
  std::string line;
  std::string cell;

  size_t maxcols = 0;
  while(file) {
    std::getline(file,line);
    std::stringstream lineStream(line);
    row.clear();

    while(std::getline(lineStream, cell, delim)) {
      boost::trim(cell);
      row.push_back(cell);
    }

    if(!row.empty()) {
      data.push_back(row);
      if(row.size() > maxcols) {
        maxcols = row.size();
      }
    }
  }
  
  cv::Mat_<T> ret(data.size(), maxcols);        
  for(int row = 0; row < ret.rows; ++row) {
    for(int col = 0; col < ret.cols; ++col) {
      if( col < int(data[row].size()) ) {
        ret(row, col) = boost::lexical_cast<T>(data[row][col]);
      }
      else {
        ret(row, col) = defaultval;
      }
    }
  }

  return ret;
}


} //ns ocv
} //ns rv

#endif
