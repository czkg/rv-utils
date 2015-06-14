#include <rv/ml/rf/splitfunction/splitfunctionpixelvalue.h>

#include <boost/serialization/base_object.hpp>


namespace rv {namespace rf {
boost::shared_ptr< rv::rf::SplitFunction > rv::rf::SplitFunctionPixelValue::Generate() const {
  boost::shared_ptr<SplitFunctionPixelValue> split_fcn = boost::make_shared<SplitFunctionPixelValue>();
  split_fcn->slice_ = rv::rand::Rand<int>::Uniform(0, gen_n_slices_);
  
  split_fcn->pt_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
  split_fcn->pt_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  
  return split_fcn;
}
float SplitFunctionPixelValue::Compute(rv::rf::SamplePtr sample) const {
  //std::cout << "generated pt: " << pt_ << "; sample: " << sample->channels() 
  //  << " / " << sample->height() << " / " << sample->width() << std::endl;
  float val = (*sample)(slice_, pt_.y, pt_.x);
  return val;
}


} //ns rf
} //ns rv
