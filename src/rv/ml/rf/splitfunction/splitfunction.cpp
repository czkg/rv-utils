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

#include <rv/ml/rf/splitfunction/splitfunction.h>

#include <iostream>
#include <fstream>


namespace rv {
namespace rf {

void SplitFunction::SetUp(const SplitFunctionParameter& param, 
    const std::vector<SamplePtr>& samples) {

  gen_n_slices_ = param.gen_n_slices();
  std::cout << "[INFO] gen_n_slices: " << param.gen_n_slices() << std::endl;
  
  if(param.gen_space() == SplitFunctionParameter::LINEAR) {
    gen_x_ = rv::ocv::linspace(param.gen_x_from(), param.gen_x_to(), param.gen_x_n());
    gen_y_ = rv::ocv::linspace(param.gen_y_from(), param.gen_y_to(), param.gen_y_n());
  }
  else if(param.gen_space() == SplitFunctionParameter::LOG_10) {
    gen_x_ = rv::ocv::logspace(param.gen_x_from(), param.gen_x_to(), param.gen_x_n() / 2);
    for(size_t idx = 0; idx < param.gen_x_n() / 2; ++idx) {
      gen_x_.push_back(-gen_x_[idx]);
    }
    gen_y_ = rv::ocv::logspace(param.gen_y_from(), param.gen_y_to(), param.gen_y_n() / 2);
    for(size_t idx = 0; idx < param.gen_x_n() / 2; ++idx) {
      gen_y_.push_back(-gen_y_[idx]);
    }
  }
  else if(param.gen_space() == SplitFunctionParameter::DATA_LINEAR) {
    SamplePtr sample = samples[0];
    gen_x_ = rv::ocv::linspace(float(0), float(sample->width() - 1), float(sample->width()));
    gen_y_ = rv::ocv::linspace(float(0), float(sample->height() - 1), float(sample->height()));
  }

  
  std::cout << "[INFO] gen_x_space: ";
  for(size_t idx = 0; idx < gen_x_.size(); ++idx) {
    std::cout << gen_x_[idx] << " ";
  }
  std::cout << std::endl;
  
  std::cout << "[INFO] gen_y_space: ";
  for(size_t idx = 0; idx < gen_y_.size(); ++idx) {
    std::cout << gen_y_[idx] << " ";
  }
  std::cout << std::endl;
}


bool SplitFunction::Split(SamplePtr sample) const {
  return Compute(sample) < threshold_;
}



} //ns rf
} //ns rv
