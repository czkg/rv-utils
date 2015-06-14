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
