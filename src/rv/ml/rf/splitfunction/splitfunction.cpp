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
