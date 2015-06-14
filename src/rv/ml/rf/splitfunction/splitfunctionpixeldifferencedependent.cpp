#include <rv/ml/rf/splitfunction/splitfunctionpixeldifferencedependent.h>

namespace rv {
namespace rf {

boost::shared_ptr< rv::rf::SplitFunction > rv::rf::SplitFunctionPixelDifferenceDependent::Generate() const {
  boost::shared_ptr<SplitFunctionPixelDifferenceDependent> split_fcn = boost::make_shared<SplitFunctionPixelDifferenceDependent>();
  
  split_fcn->slice_ = rv::rand::Rand<int>::Uniform(0, gen_n_slices_);
  
  split_fcn->p1_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
  split_fcn->p1_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  if(gen_fix_one_) {
    split_fcn->p2_.x = 0;
    split_fcn->p2_.y = 0;
  }
  else {
    split_fcn->p2_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
    split_fcn->p2_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  }
  
  return split_fcn;
}

float rv::rf::SplitFunctionPixelDifferenceDependent::Compute(rv::rf::SamplePtr sample) const {
  float dependent = (*sample)(slice_, 0, 0);

  int x1 = p1_.x / dependent;
  int x2 = p2_.x / dependent;
  int y1 = p1_.y / dependent;
  int y2 = p2_.y / dependent;

  // std::cout << "diff " << x1 << "/" << y1 << ", " << x2 << "/" << y2 << std::endl;

  float val1 = (*sample)(slice_, y1, x1);
  float val2 = (*sample)(slice_, y2, x2);
  return val1 - val2;
}


} //ns rf
} //ns rv
