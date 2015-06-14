#ifndef RV_OCV_LINALG_H
#define RV_OCV_LINALG_H

#include <opencv2/core/core.hpp>

#include <rv/log/log.h>


namespace rv {
namespace ocv {

template <typename T, int axis>
inline cv::Mat_<T> sum(const cv::Mat_<T>& in) {
  //sum up cols = col vector
  if(axis == 0) {
    cv::Mat_<T> sum(in.rows, 1, T(0));
    for(int col = 0; col < in.cols; ++col) {
      sum = sum + in.col(col);
    }
    
    return sum;
  }
  
  //sum up rows => row vector
  if(axis == 1) {
    cv::Mat_<T> sum(1, in.cols, T(0));
    for(int row = 0; row < in.rows; ++row) {
      sum = sum + in.row(row);
    }
    
    return sum;
  }
}


template <typename T>
inline double dist2(T v1, T v2) {
  double diff = v1 - v2;
  return std::abs(diff);
}


template <typename T>
inline cv::Mat_<double> dist2(const cv::Mat_<T>& mat1, const cv::Mat_<T> mat2) {
  cv::Mat_<double> dist(1, mat1.cols);
  
  if(mat1.cols == mat2.cols) {
    dist = mat1 - mat2;
  }
  else if(mat2.cols == 1) {
    for(int col = 0; col < mat1.cols; ++col) {
      dist.col(col) = mat1.col(col) - mat2;
    }
  }
  else {
    LOG_ERROR << "mat2.cols != 1 && mat1.cols != mat2.cols";
  }
  
  dist = dist.mul(dist);
  dist = sum<double, 1>(dist);
  cv::sqrt(dist, dist);

  return dist;
}


template <typename T, int cn>
inline double dist2(cv::Vec<T, cn> v1, cv::Vec<T, cn> v2) {
    double dist = 0;

    if(cn > 0) {
      double val = v1(0) - v2(0);
      dist = dist + val * val;
    }

    if(cn > 1) {
      double val = v1(1) - v2(1);
      dist = dist + val * val;
    }

    if(cn > 2) {
      double val = v1(2) - v2(2);
      dist = dist + val * val;
    }
    
    if(cn > 3) {
      for(int i = 3; i < cn; ++i) {
        double val = v1(i) - v2(i);
        dist = dist + val * val;
      }
    }

  return std::sqrt(dist);
}


template <typename T1, typename T2>
inline double dist2(cv::Point_<T1> v1, cv::Point_<T2> v2) {
  double dx = v1.x - v2.x;
  double dy = v1.y - v2.y;
  return std::sqrt(dx * dx + dy * dy);
}



template <typename T>
inline std::vector<T> linspace(const T& from, const T& to, int n) {
  double step = T(to - from) / double(n - 1); //if not double, it is not working with [T = int]]
  
  std::vector<T> space(n);
  space[0] = from;
  for(int i = 1; i < n - 1; ++i) {
    space[i] = from + i * step;
  }
  space[n - 1] = to;
  
  return space;
}


template <typename T>
inline std::vector<T> logspace(const T& from, const T& to, int n, T base = 10) {
  std::vector<double> lins = linspace(double(from), double(to), n);
  
  std::vector<T> space(n);
  for(int i = 0; i < n; ++i) {
    space[i] = std::pow(base, lins[i]);
  }
  
  return space;
}


} //cv
} //rv

#endif 
