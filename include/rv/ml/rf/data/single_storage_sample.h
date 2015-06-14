#ifndef RV_RF_SINGLE_MAT_SAMPLE_H
#define RV_RF_SINGLE_MAT_SAMPLE_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include <rv/log/log.h>
#include <rv/ml/rf/common.h>
#include <rv/ml/rf/data/sample.h>


namespace rv {
namespace rf {
    
class SingleStorageSample : public Sample {    
public:
  SingleStorageSample() {}

  SingleStorageSample(RfMatPtr mat, int col) : mat_(mat), col_(col) {}
  
  virtual ~SingleStorageSample() {}
  
  
  virtual float operator()(int c, int h, int w) const;
  
  virtual int channels() const { return 1; }
  virtual int height() const { return mat_->rows(); }
  virtual int width() const { return 1; }

protected:
  RfMatPtr mat_;
  int col_;
};
    
}
}


#endif
