#include <rv/ml/rf/data/patchsample.h>

float rv::rf::PatchSample::operator()(int c, int h, int w) const {
  int h_ = h;  
  int w_ = w;
  if(c >= 0 && c < patches_.size()) {
    h = patches_[c].rows / 2 + h;
    w = patches_[c].cols / 2 + w;
    if(h >= 0 && w >= 0 && h < patches_[c].rows && w < patches_[c].cols) {
      return patches_[c](h, w);
    }
    else {
      LOG_ERROR << "invalid access at " << c << "/" << h << "/" << w << " with vec " << h_ << "/" << w_;
    }
  }
  else {
    LOG_ERROR << "invalid access at " << c << "/" << h << "/" << w << " with vec " << h_ << "/" << w_;
  }
}
