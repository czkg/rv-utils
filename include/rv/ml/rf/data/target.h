#ifndef RF_TARGET_H
#define RF_TARGET_H

#include <fstream>

#include <boost/shared_ptr.hpp>

#include <opencv2/core/core.hpp>

#include <rv/ml/rf/common.h>

namespace rv {
namespace rf {
    
class Target {    
public:
  Target(RfMatPtr data) : data_(data), weight_(1.0) {}
  Target(RfMatPtr data, float weight) : data_(data), weight_(weight) {}
  
  Target(int label, int max_label) {
    data_ = CreateRfMatZero(1, max_label);
    (*data_)(0, label) = 1.0;
    weight_ = 1.0;
  }
  
  Target(int label, int max_label, float weight) {
    data_ = CreateRfMatZero(1, max_label);
    (*data_)(0, label) = weight;
    weight_ = weight;
  }
  
  virtual ~Target() {}
  
  RfMatPtr data() const { return data_; }
  float weight() const { return weight_; }
  
private:
  RfMatPtr data_;
  float weight_;

};

typedef boost::shared_ptr<Target> TargetPtr;
typedef std::vector<TargetPtr> VecTargetPtr;
typedef boost::shared_ptr<VecTargetPtr> VecPtrTargetPtr;

}
}


#endif
