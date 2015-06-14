#ifndef RF_SPLITFUNCTIONPIXELVALUE_H
#define RF_SPLITFUNCTIONPIXELVALUE_H

#include <fstream>

#include <opencv2/core/core.hpp>
#include <boost/make_shared.hpp>

#include <rv/ml/rf/splitfunction/splitfunction.h>

#include <rv/rand/rand.h>
#include <rv/ocv/linalg.h>


namespace rv {
namespace rf {
    
class SplitFunctionPixelValue : public SplitFunction {
public:
  SplitFunctionPixelValue() {}
  virtual ~SplitFunctionPixelValue() {}
  
  virtual boost::shared_ptr<SplitFunction> Copy() const {
    boost::shared_ptr<SplitFunctionPixelValue> split_fcn = boost::make_shared<SplitFunctionPixelValue>();
    split_fcn->threshold_ = threshold_;
    split_fcn->slice_ = slice_;
    split_fcn->pt_ = pt_;

    return split_fcn;
  }

  
  virtual boost::shared_ptr<SplitFunction> Generate() const;
  
  virtual float Compute(SamplePtr sample) const;
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    SplitFunction::Save(ar);

    ar << slice_;
    ar << pt_.x;
    ar << pt_.y;
  }

  virtual void Load(rv::io::SerializationIn& ar) {
    SplitFunction::Load(ar);

    ar >> slice_;
    ar >> pt_.x;
    ar >> pt_.y;
  }
  
  virtual SplitFunctionParameter::SplitFunctionType type() const { return SplitFunctionParameter::PIXEL_VALUE; }
    
private:
  int slice_;
  cv::Point pt_;

DISABLE_COPY_AND_ASSIGN(SplitFunctionPixelValue);
};


}
}

#endif
