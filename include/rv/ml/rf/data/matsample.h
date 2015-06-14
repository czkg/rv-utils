#ifndef RV_RF_MAT_SAMPLE_H
#define RV_RF_MAT_SAMPLE_H

#include <vector>


#include <boost/shared_ptr.hpp>

#include <rv/log/log.h>
#include <rv/ml/rf/common.h>
#include <rv/ml/rf/data/sample.h>


namespace rv {
namespace rf {
    
class MatSample : public Sample {    
public:
  MatSample() {}

  MatSample(RfMatPtr mat) : mat_(mat) {}
  
  virtual ~MatSample() {}
  
  
  virtual float operator()(int c, int h, int w) const;
  
  virtual int channels() const { return 1; }
  virtual int height() const { return mat_->rows(); }
  virtual int width() const { return mat_->cols(); }

protected:    
  RfMatPtr mat_;
};
    
}
}


#endif
