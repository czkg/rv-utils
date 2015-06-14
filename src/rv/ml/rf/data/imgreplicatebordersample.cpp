#include <rv/ml/rf/data/imgsample.h>

float rv::rf::ImgReplicateBorderSample::operator()(int c, int h, int w) const {
  h = this->cy_ + h;
  w = this->cx_ + w;
  if(h < 0) h = 0;
  if(w < 0) w = 0;
  if(h >= this->imgs_[c].rows) h = this->imgs_[c].rows - 1;
  if(w >= this->imgs_[c].cols) w = this->imgs_[c].cols - 1;
  
  return this->imgs_[c](h, w);
}