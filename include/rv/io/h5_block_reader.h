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

#ifndef RV_IO_H5_BLOCK_READER_H
#define RV_IO_H5_BLOCK_READER_H

#include <iostream>
#include <fstream>

#include "hdf5.h"
#include "hdf5_hl.h"

#include <opencv2/core/core.hpp>

#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>

#include <rv/log/log.h>

namespace rv {
namespace io {
    
class H5BlockReader {
public:
  H5BlockReader(boost::filesystem::path list_path, std::string dataset_name) :
    dataset_name_(dataset_name), data_(0) {
    
    std::ifstream source_file(list_path.c_str());
    if (source_file.is_open()) {
      std::string line;
      while (source_file >> line) {
        h5_paths_.push_back(line);
      }
    }
    source_file.close();
    
    std::cout << "[INFO] listed " << h5_paths_.size() << " hdf5 paths:" << std::endl;
    for(size_t idx = 0; idx < h5_paths_.size(); ++idx) {                
      std::cout << "[INFO]    " << h5_paths_[idx] << std::endl;
    }
            
    current_hdf5_path_ = 0;
    current_num_ = 0;
    
    if(h5_paths_.size() > 0) {
      loadHdf5();
    }
  }
  
  virtual ~H5BlockReader() {
    if(data_ != 0) {
      delete[] data_;
    }
  }
  
  virtual bool hasNext() const {
    return (current_hdf5_path_ < h5_paths_.size()) && (current_num_ < dims_[0]);
  }
  
  virtual void next() {
    current_num_++;
    if(current_num_ == dims_[0]) {
      current_hdf5_path_++;
      current_num_ = 0;
      
      if(current_hdf5_path_ < h5_paths_.size()) {
        loadHdf5();
      }
    }
  }
  
  
  virtual std::vector<cv::Mat_<float> > data() const {
    std::vector<cv::Mat_<float> > mats(dims_[1], cv::Mat_<float>(height(), width()));
    
    int idx = current_num_ * (channels() * height() * width());
    for(int c = 0; c < channels(); ++c) {
      for(int h = 0; h < height(); ++h) {
        for(int w = 0; w < width(); ++w) {
          mats[c](h, w) = data_[idx];
          idx++;
        }
      }
    }
    
    return mats;
  }
  
  virtual cv::Mat_<float> data(int c) const {
    cv::Mat_<float> mat(height(), width());
    
    int idx = current_num_ * (channels() * height() * width()) + c * (height() * width());
    for(int h = 0; h < height(); ++h) {
      for(int w = 0; w < width(); ++w) {
        mat(h, w) = data_[idx];
        idx++;
      }
    }
    
    return mat;
  }
  
  virtual float data(int c, int h, int w) {
    int idx = current_num_ * (channels() * height() * width()) + c * (height() * width()) + h * height() + w;
    return data_[idx];
  }
  
  
  virtual int channels() const { return dims_[1]; }
  virtual int height() const { return dims_[2]; }
  virtual int width() const { return dims_[3]; }
  
protected:
    
  virtual void loadHdf5() {
    boost::filesystem::path hdf5_path = h5_paths_[current_hdf5_path_];
    
    //open hdf5
    LOG_INFO << "[INFO] Loading h5 file " << hdf5_path;
    hid_t file_id = H5Fopen(hdf5_path.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) {
      LOG_ERROR << "Failed opening h5 file " << hdf5_path.string();
    }
    
    //load dims
    int ndims;
    herr_t status = H5LTget_dataset_ndims(file_id, dataset_name_.c_str(), &ndims);
    if (status < 0) {
      LOG_ERROR << "Failed to get dataset ndims for " << dataset_name_;
    }

    dims_.resize(ndims);
    
    H5T_class_t class_;
    status = H5LTget_dataset_info(file_id, dataset_name_.c_str(), dims_.data(), &class_, NULL);
    if (status < 0) {
      LOG_ERROR << "Failed to get dataset info for " << dataset_name_;
    }
    if (class_ != H5T_FLOAT) {
      LOG_ERROR << "Expected float or double data";
    }

    while(dims_.size() < 4) {
      dims_.push_back(1);
    }
    
    //load data
    if(data_ != 0) {
      delete[] data_;
    }
    data_ = new float[dims_[0] * channels() * height() * width()];
    status = H5LTread_dataset_float(file_id, dataset_name_.c_str(), data_);
    if (status < 0) {
      LOG_ERROR << "Failed to read float dataset " << dataset_name_;
    }
    
    //close hdf5
    status = H5Fclose(file_id);
    if (status < 0) {
      LOG_ERROR << "Failed closing h5 file " << hdf5_path.string();
    }
  }
    
private:
  std::vector<boost::filesystem::path> h5_paths_;
  std::string dataset_name_;
  
  int current_hdf5_path_;
  int current_num_;
  
  std::vector<hsize_t> dims_;
  float* data_;
};

} //ns io
} //ns rv

#endif
