#include <rv/ml/rf/splitevaluator/regressionsplitevaluator.h>

float rv::rf::VarianceReductionRegressionSplitEvaluator::Purity(
    const std::vector<TargetPtr>& targets) const {
  
  float var = 0;
  for(size_t target_idx_1 = 0; target_idx_1 < targets.size(); ++target_idx_1) {
    RfMatPtr t_1 = targets[target_idx_1]->data();
    
    for(size_t target_idx_2 = 0; target_idx_2 < targets.size(); ++target_idx_2) {
      RfMatPtr t_2 = targets[target_idx_2]->data();
      
      for(int row = 0; row < t_1->rows(); ++row) {
        for(int col = 0; col < t_1->cols(); ++col) {
          float diff = (*t_1)(row, col) - (*t_2)(row, col);
          var = var + diff * diff;
        }
      }
    }
  }
  
  return var;
}
