#include <rv/ml/rf/data/imgsample.h>

float rv::rf::ImgSample::operator()(int c, int h, int w) const {
  h = this->cy_ + h;
  w = this->cx_ + w;
  if(c >= 0 && c < imgs_.size() && h >= 0 && w >= 0 && h < imgs_[c].rows && w < imgs_[c].cols) {
    return imgs_[c](h, w);
  }
  else {
    LOG_ERROR << "invalid access";
  }
}
