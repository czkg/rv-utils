#include <rv/ml/rf/data/matsample.h>

float rv::rf::MatSample::operator()(int c, int h, int w) const {
  if(c != 0 || h < 0 || w < 0 || h >= mat_->rows() || w >= mat_->cols()) {
    LOG_ERROR << "invalid access at " << c << "/" << h << "/" << w 
      << "; patch: " << mat_->rows() << "x" << mat_->cols();
  }

  return (*mat_)(h, w);
}
