#include <rv/ml/rf/data/single_storage_sample.h>

float rv::rf::SingleStorageSample::operator()(int c, int h, int w) const {
  if(c != 0 || w != 0  || h < 0|| h >= mat_->rows()) {
    LOG_ERROR << "invalid access at " << c << "/" << h << "/" << w 
      << "; patch: " << mat_->rows() << "x" << 1;
  }

  return (*mat_)(h, col_);
}
