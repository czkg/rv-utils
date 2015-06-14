#ifndef RV_RF_SPLITEVALUATOR_H
#define RV_RF_SPLITEVALUATOR_H

#include <vector>

#include <rv/ml/rf/data/sample.h>
#include <rv/ml/rf/data/target.h>

namespace rv {
namespace rf {
    
class SplitEvaluator {    
public:
  SplitEvaluator(bool normalize, float weight) : 
    normalize_(normalize), weight_(weight)
  {}

  virtual ~SplitEvaluator() {}
  
  virtual float Eval(const std::vector<TargetPtr>& lefttargets, 
      const std::vector<TargetPtr>& righttargets) const;
      
protected:
  virtual float Purity(const std::vector<TargetPtr>& targets) const = 0;
  
protected:
  bool normalize_;
  float weight_;
};

typedef boost::shared_ptr<SplitEvaluator> SplitEvaluatorPtr;

}
}

#endif
