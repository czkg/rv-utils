#include <rv/ml/rf/splitevaluator/regressionsplitevaluator.h>

float rv::rf::WeightedTraceCovRegressionSplitEvaluator::Purity(
    const std::vector<TargetPtr>& targets) const {
  
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMat mu(rows, cols);
  mu.setZero();

  //compute mean
  for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
    if(weighted_mean_) {
      float w = targets[target_idx]->weight();
      mu = mu + w * (*(targets[target_idx]->data()));
    }
    else {
      mu += (*(targets[target_idx]->data()));
    }
  }
  mu = mu * (1.0 / float(targets.size()));
  
  //compute variances
  RfMat sigma(rows, cols);
  sigma.setZero();
  for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
    RfMat diff = (*(targets[target_idx]->data())) - mu;
    
    float w = targets[target_idx]->weight();
    sigma = sigma + w * diff.array().square().matrix();
  }
  sigma *= (1.0 / double(targets.size()));
  
  //compute trace
  double tr = sigma.sum();
  
  return tr;
}
