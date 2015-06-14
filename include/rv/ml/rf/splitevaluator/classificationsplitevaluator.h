#ifndef RV_RF_CLASSIFICATIONSPLITEVALUATOR_H
#define RV_RF_CLASSIFICATIONSPLITEVALUATOR_H

#include <rv/ml/rf/splitevaluator/splitevaluator.h>

namespace rv {
namespace rf {

class InformationGainClassificationSplitEvaluator : public SplitEvaluator {    
public:
  InformationGainClassificationSplitEvaluator(bool normalize, float weight) 
      : SplitEvaluator(normalize, weight) {}
  virtual ~InformationGainClassificationSplitEvaluator() {}
  
protected:
  virtual float Purity(const std::vector<TargetPtr>& targets) const;
};


class GiniClassificationSplitEvaluator : public SplitEvaluator {    
public:
  GiniClassificationSplitEvaluator(bool normalize, float weight) 
      : SplitEvaluator(normalize, weight) {}
  virtual ~GiniClassificationSplitEvaluator() {}
  
protected:
  virtual float Purity(const std::vector<TargetPtr>& targets) const;
};
    
}
}

#endif
