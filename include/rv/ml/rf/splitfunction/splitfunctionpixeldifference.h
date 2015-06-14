#ifndef RF_SPLITFUNCTIONPIXELDIFFERENCE_H
#define RF_SPLITFUNCTIONPIXELDIFFERENCE_H

#include <fstream>

#include <opencv2/core/core.hpp>
#include <boost/make_shared.hpp>

#include <rv/ml/rf/splitfunction/splitfunction.h>
#include <rv/rand/rand.h>


namespace rv {
namespace rf {
    
class SplitFunctionPixelDifference : public SplitFunction {
public:
  SplitFunctionPixelDifference() {}
  virtual ~SplitFunctionPixelDifference() {}
  
  virtual boost::shared_ptr<SplitFunction> Copy() const {
    boost::shared_ptr<SplitFunctionPixelDifference> split_fcn = boost::make_shared<SplitFunctionPixelDifference>();
    split_fcn->threshold_ = threshold_;
    split_fcn->slice_ = slice_;
    split_fcn->p1_ = p1_;
    split_fcn->p2_ = p2_;

    return split_fcn;
  }

  
  virtual boost::shared_ptr<SplitFunction> Generate() const;
  
  virtual float Compute(SamplePtr sample) const;
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    SplitFunction::Save(ar);
    ar << slice_;
    ar << p1_.x;
    ar << p1_.y;
    ar << p2_.x;
    ar << p2_.y;
  }
  
  virtual void Load(rv::io::SerializationIn& ar) {
    SplitFunction::Load(ar);

    ar >> slice_;
    ar >> p1_.x;
    ar >> p1_.y;
    ar >> p2_.x;
    ar >> p2_.y;
  }
  
  virtual SplitFunctionParameter::SplitFunctionType type() const { return SplitFunctionParameter::PIXEL_DIFFERENCE; }
    
private:
  int slice_;
  cv::Point p1_;
  cv::Point p2_;    

DISABLE_COPY_AND_ASSIGN(SplitFunctionPixelDifference);
};

}
}

#endif
