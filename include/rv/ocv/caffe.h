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