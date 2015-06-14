#ifndef RV_EIGEN_IO_CSV_H
#define RV_EIGEN_IO_CSV_H

#include <fstream>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <Eigen/Dense>


namespace rv {
namespace eigen {

  
template <typename EigenMat>
inline void WriteCsv(std::ostream& out, const EigenMat& mat, 
    boost::format fmt = boost::format("% .8e")) {

  for(int row = 0; row < mat.rows(); ++row) {
    for(int col = 0; col < mat.cols(); ++col) {
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


template <typename EigenMat>
inline void WriteCsv(const boost::filesystem::path& file, const EigenMat& mat, 
    boost::format fmt = boost::format("% .8e")) {

  std::ofstream out(file.c_str());
  WriteCsv(out, mat, fmt);
  out.close();
}


template <typename T, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
inline void ReadCsv(const boost::filesystem::path& p, 
    Eigen::Matrix<T, Rows, Cols, Options, MaxRows, MaxCols>& mat, 
    char delim = ',', T defaultval = 0) {
  
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
  
  mat.resize(data.size(), maxcols);
  for(int row = 0; row < mat.rows(); ++row) {
    for(int col = 0; col < mat.cols(); ++col) {
      if( col < int(data[row].size()) ) {
        mat(row, col) = boost::lexical_cast<T>(data[row][col]);
      }
      else {
        mat(row, col) = defaultval;
      }
    }
  }
}


} //ns io
} //ns rv

#endif
