#ifndef RV_RF_SPLITFUNCTION_H
#define RV_RF_SPLITFUNCTION_H

#include <rv/ml/rf/data/sample.h>
#include <rv/ml/rf/proto/rf.pb.h>
#include <rv/ml/rf/common.h>

#include <rv/ocv/linalg.h>
#include <rv/io/serialization/serialization.h>


namespace rv {
namespace rf {
    
class SplitFunction {
public:
  SplitFunction() {}
  virtual ~SplitFunction() {}

  virtual boost::shared_ptr<SplitFunction> Copy() const = 0;
  
  virtual void SetUp(const SplitFunctionParameter& param, 
      const std::vector<SamplePtr>& samples);
  
  virtual boost::shared_ptr<SplitFunction> Generate() const = 0;
  
  virtual float Compute(SamplePtr sample) const = 0;
  virtual SplitFunctionParameter::SplitFunctionType type() const = 0;
  
  virtual bool Split(SamplePtr sample) const;
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    ar << threshold_;
  }

  virtual void Load(rv::io::SerializationIn& ar) {
    ar >> threshold_;
  }
  
  virtual float threshold() const { return threshold_; }
  virtual void set_threshold(float threshold) { threshold_ = threshold; }
    
protected:
  float threshold_;
  
  //generate parameters
  int gen_n_slices_;
  std::vector<float> gen_x_;
  std::vector<float> gen_y_;
  bool gen_fix_one_;
};

typedef boost::shared_ptr<SplitFunction> SplitFunctionPtr;

}
}

#endif
