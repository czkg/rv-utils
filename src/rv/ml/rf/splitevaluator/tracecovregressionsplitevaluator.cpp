#include <rv/ml/rf/splitevaluator/regressionsplitevaluator.h>

float rv::rf::TraceCovRegressionSplitEvaluator::Purity(
    const std::vector<TargetPtr>& targets) const {
  
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMat mu(rows, cols);
  mu.setZero();

  //compute mean
  for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
    mu += (*(targets[target_idx]->data()));
  }
  mu = mu * (1.0 / float(targets.size()));
  
  //compute variances
  RfMat sigma(rows, cols);
  sigma.setZero();
  for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
    RfMat diff = (*(targets[target_idx]->data())) - mu;
    
    sigma = sigma + diff.array().square().matrix();
  }
  sigma *= (1.0 / double(targets.size()));
  
  //compute trace
  // double tr = 0;
  // for(int row = 0; row < rows; ++row) {
  //   for(int col = 0; col < cols; ++col) {
  //     tr += sigma(row, col);
  //   }
  // }
  double tr = sigma.sum();
  
  return tr;
}
