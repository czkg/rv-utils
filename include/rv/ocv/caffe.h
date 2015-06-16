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

#ifndef RV_OCV_CAFFE_H
#define RV_OCV_CAFFE_H

#include <boost/make_shared.hpp>

#include <opencv2/core/core.hpp>

#include <caffe/blob.hpp>

namespace rv {
namespace ocv {

template <typename Dtype>
boost::shared_ptr<caffe::Blob<Dtype> > mat2Blob(const std::vector<cv::Mat_<Dtype> >& mats) {
  int num = mats.size();
  int channels = 1;
  int height = mats[0].rows;
  int width = mats[0].cols;

  boost::shared_ptr<caffe::Blob<Dtype> > blob = boost::make_shared<caffe::Blob<Dtype> >(num, channels, height, width);
  Dtype* blob_data = blob->mutable_cpu_data();

  for(int n = 0; n < num; ++n) {
    cv::Mat_<Dtype> mat = mats[n];

    for(int c = 0; c < channels; ++c) {
      for(int h = 0; h < height; ++h) {
        for(int w = 0; w < width; ++w) {
          int blob_data_idx = n * (channels * height * width) +
              c * (height * width) + h * (width) + w;
          blob_data[blob_data_idx] = mat(h, w);
        }
      }
    }
  }

  return blob;
}

template <typename Dtype>
boost::shared_ptr<caffe::Blob<Dtype> > mat2Blob(const cv::Mat_<Dtype>& mat) {
  std::vector<cv::Mat_<Dtype> > mats;
  mats.push_back(mat);

  return mat2Blob(mats);
}



template <typename Dtype>
cv::Mat_<Dtype> blob2Mat(const boost::shared_ptr<caffe::Blob< Dtype> > blob, int n, int c) {
  int num = blob->num();
  int channels = blob->channels();
  int height = blob->height();
  int width = blob->width();
  
  cv::Mat_<Dtype> mat(height, width);
  for(int h = 0; h < height; ++h) {
    for(int w = 0; w < width; ++w) {
      mat(h, w) = blob->cpu_data()[blob->offset(n, c, h, w)];
    }
  }
  
  return mat;
}

}
}

#endif
