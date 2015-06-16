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

#ifndef RV_OCV_CONVERT_H
#define RV_OCV_CONVERT_H

#include <typeinfo>
#include <stdexcept>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <rv/log/log.h>

namespace rv {
namespace ocv {

template <typename To, typename From>
inline cv::Mat_<To> convert(const cv::Mat_<From>& from, From alpha = 1, From beta = 0) {
  cv::Mat_<To> to(from.rows, from.cols);
  for(int row = 0; row < from.rows; ++row) {
    for(int col = 0; col < from.cols; ++col) {
      From val_from = from(row, col) * alpha + beta;
      To val_to = val_from;
      
      if(typeid(val_to) == typeid(cv::Vec3b) && (typeid(val_from) == typeid(float) || typeid(val_from) == typeid(double))) {
        val_to = cv::Vec3b(val_from, val_from, val_from);
      }
      
      to(row, col) = val_to;
    }
  }

  return to;
}


template <typename T, int N>
inline void mat2vecs(const cv::Mat_<T>& mat, std::vector<cv::Vec<T, N> >& vecs) {
  bool row_vecs;
  if(mat.cols == N) {
    row_vecs = true;
  }
  else if(mat.rows == N) {
    row_vecs = false;
  }
  else {
    LOG_ERROR << "can not convert mat to vecs - dim";
  }
  
  cv::Mat_<T> copy_mat = row_vecs ? mat : mat.t();
  
  vecs.resize(copy_mat.rows);
  for(int row = 0; row < copy_mat.rows; ++row) {
    for(int col = 0; col < N; ++col) {
      vecs[row](col) = mat(row, col);
    }
  }
}


template <typename T, int N>
inline cv::Mat_<T> vecs2mat(const std::vector<cv::Vec<T, N> >& vecs) {
  cv::Mat_<T> mat(vecs.size(), N);
  
  for(int row = 0; row < mat.rows; ++row) {
    for(int col = 0; col < mat.cols; ++col) {
      mat(row, col) = vecs[row](col);
    }
  }
  
  return mat;
}


template <typename T>
inline cv::Mat_<T> mats2mat(const std::vector<cv::Mat_<T> >& mats) {
  int rows = 0;
  int cols = 0;
  for(size_t mat_idx = 0; mat_idx < mats.size(); ++mat_idx) {
    rows = rows + mats[mat_idx].rows;
    if(cols < mats[mat_idx].cols) {
      cols = mats[mat_idx].cols;
    }
  }
  
  cv::Mat_<T> mat(rows, cols);
  
  rows = 0;
  for(size_t mat_idx = 0; mat_idx < mats.size(); ++mat_idx) {
    for(int row = 0; row < mats[mat_idx].rows; ++row) {
      for(int col = 0; col < mats[mat_idx].cols; ++col) {
        mat(row + rows, col) = mats[mat_idx](row, col);
      }
    }
    rows = rows + mats[mat_idx].rows;
  }
  
  return mat;
}


template <typename T>
inline cv::Mat_<T> pts2mat(const std::vector<cv::Point_<T> >& pts) {
  cv::Mat_<T> mat(pts.size(), 2);
  for(int i = 0; i < pts.size(); ++i) {
    mat(i, 0) = pts[i].x;
    mat(i, 1) = pts[i].y;
  }

  return mat;
}


template <typename T>
inline cv::Mat_<T> clamp(const cv::Mat_<T>& map, T min, T max) {
  cv::Mat_<T> retmap = map.clone();
  for(int row = 0; row < retmap.rows; ++row) {
    for(int col = 0; col < retmap.cols; ++col) {
      if(retmap(row, col) > max) {
        retmap(row, col) = max;
      }
      else if(retmap(row, col) < min) {
        retmap(row, col) = min;
      }

      retmap(row, col) = (retmap(row, col) - min) / (max - min);
    }
  }

  return retmap;
}


template <typename T>
inline cv::Mat_<T> clamp(const cv::Mat_<T>& map) {
  double min, max;
  cv::minMaxLoc(map, &min, &max);

  return clamp(map, T(min), T(max));
}


inline cv::Mat_<cv::Vec3b> rgb2gray3(const cv::Mat_<cv::Vec3b>& img) {
  cv::Mat_<cv::Vec3b> img_gray(img.rows, img.cols);
  for(int row = 0; row < img_gray.rows; ++row) {
    for(int col = 0; col < img_gray.cols; ++col) {
      cv::Vec3b in = img(row, col);
      uchar val = 0.114 * in(0) + 0.587 * in(1) + 0.299 * in(2);
      img_gray(row, col) = cv::Vec3b(val, val, val);
    }
  }

  return img_gray;
}


inline cv::Mat_<float> rgb2gray(const cv::Mat_<cv::Vec3b>& img) {
  cv::Mat_<float> img_gray(img.rows, img.cols);
  for(int row = 0; row < img_gray.rows; ++row) {
    for(int col = 0; col < img_gray.cols; ++col) {
      cv::Vec3b in = img(row, col);
      float val = ( 0.114 * in(0) + 0.587 * in(1) + 0.299 * in(2) ) / 255.0;
      img_gray(row, col) = val;
    }
  }

  return img_gray;
}


inline cv::Mat_<cv::Vec3b> rgb2YCrCb(const cv::Mat_<cv::Vec3b>& img) {
  cv::Mat_<cv::Vec3b> imgC;
  cv::cvtColor(img, imgC, CV_BGR2YCrCb);
  return imgC;
}


inline cv::Mat_<cv::Vec3b> yCrCb2Rgb(const cv::Mat_<cv::Vec3b>& img) {
  cv::Mat_<cv::Vec3b> imgC;
  cv::cvtColor(img, imgC, CV_YCrCb2BGR);
  return imgC;
}


inline cv::Vec3f hsv2Rgb(const cv::Vec3f& hsv) {
  float h = hsv(0);
  float s = hsv(1);
  float v = hsv(2);

  float h60 = h / 60.0;
  float h60f = floor(h60);
  int hi = int(h60f) % 6;
  float f = h60 - h60f;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  cv::Vec3f rgb = cv::Vec3f(0, 0, 0);
  if(hi == 0) {
    rgb = cv::Vec3f(v, t, p);
  }
  else if (hi == 1) {
    rgb = cv::Vec3f(q, v, p);
  }
  else if (hi == 2) {
    rgb = cv::Vec3f(p, v, t);
  }
  else if (hi == 3) {
    rgb = cv::Vec3f(p, q, v);
  }
  else if (hi == 4) {
    rgb = cv::Vec3f(t, p, v);
  }
  else if (hi == 5) {
    rgb = cv::Vec3f(v, p, q);
  }

  return cv::Vec3f(rgb(2), rgb(1), rgb(0));
}




template <typename T>
inline cv::Mat_<T> roi(const cv::Mat_<T>& in, cv::Rect roi, T default_val = 0) {
  cv::Mat_<T> out(roi.height, roi.width);
  
  for(int row = 0; row < roi.height; ++row) {
    for(int col = 0; col < roi.width; ++col) {
      int row_in = roi.y + row;
      int col_in = roi.x + col;
      
      T val = default_val;
      if(row_in >= 0 && col_in >= 0 && row_in < in.rows && col_in < in.cols) {
        val = in(row_in, col_in);
      }
      
      out(row, col) = val;
    }
  }
  
  return out;
}


} //ns cv
} //ns rv

#endif 
