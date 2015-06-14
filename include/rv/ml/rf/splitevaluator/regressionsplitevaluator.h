#ifndef RV_RF_REGRESSIONSPLITEVALUATOR_H
#define RV_RF_REGRESSIONSPLITEVALUATOR_H

#include <rv/ml/rf/splitevaluator/splitevaluator.h>

#include <opencv2/core/core.hpp>

namespace rv {
namespace rf {


class TraceCovRegressionSplitEvaluator : public SplitEvaluator {    
public:
  TraceCovRegressionSplitEvaluator(bool normalize, float weight) 
      : SplitEvaluator(normalize, weight) {}
  virtual ~TraceCovRegressionSplitEvaluator() {}
  
protected:
  virtual float Purity(const std::vector<TargetPtr>& targets) const;
};

class WeightedTraceCovRegressionSplitEvaluator : public SplitEvaluator {    
public:
  WeightedTraceCovRegressionSplitEvaluator(bool normalize, float weight, 
      bool weighted_mean) 
    : SplitEvaluator(normalize, weight), weighted_mean_(weighted_mean) {}
  virtual ~WeightedTraceCovRegressionSplitEvaluator() {}
  
protected:
  virtual float Purity(const std::vector<TargetPtr>& targets) const;

private:
  bool weighted_mean_;
};


class VarianceReductionRegressionSplitEvaluator : public SplitEvaluator {    
public:
  VarianceReductionRegressionSplitEvaluator(bool normalize, float weight) 
      : SplitEvaluator(normalize, weight) {}
  virtual ~VarianceReductionRegressionSplitEvaluator() {}
  
protected:
  virtual float Purity(const std::vector<TargetPtr>& targets) const;
};

}
}

#endif
