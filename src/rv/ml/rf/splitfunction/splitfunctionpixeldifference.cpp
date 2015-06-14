#include <rv/ml/rf/splitfunction/splitfunctionpixeldifference.h>

namespace rv {
namespace rf {

boost::shared_ptr< SplitFunction > SplitFunctionPixelDifference::Generate() const {
  boost::shared_ptr<SplitFunctionPixelDifference> split_fcn = boost::make_shared<SplitFunctionPixelDifference>();
  
  split_fcn->slice_ = rv::rand::Rand<int>::Uniform(0, gen_n_slices_);
  
  split_fcn->p1_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
  split_fcn->p1_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  if(gen_fix_one_) {
    split_fcn->p2_.x = gen_x_[gen_x_.size() / 2];
    split_fcn->p2_.y = gen_y_[gen_y_.size() / 2];
  }
  else {
    split_fcn->p2_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
    split_fcn->p2_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  }
  
  return split_fcn;
}

float SplitFunctionPixelDifference::Compute(SamplePtr sample) const {
  return (*sample)(slice_, p1_.y, p1_.x) - (*sample)(slice_, p2_.y, p2_.x);
}


} //ns rf
} //ns rv
