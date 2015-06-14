#include <rv/ml/rf/leafnodefcn/regressionleafnodefcn.h>

namespace rv {
namespace rf {

LeafNodeFcnPtr MedianRegressionLeafNodeFcn::Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const std::vector<TargetPtr>& targets) const {
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMatPtr median = CreateRfMatZero(rows, cols);
  
  std::vector<float> values(targets.size());
  for(int row = 0; row < median->rows(); ++row) {
    for(int col = 0; col < median->cols(); ++col) {
      for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
        values[target_idx] = (*(targets[target_idx]->data()))(row, col);
      }
      (*median)(row, col) = rv::stat::Median(values);
    }
  }
  
  LeafNodeFcnPtr stat = boost::make_shared<MedianRegressionLeafNodeFcn>();
  stat->add_stat(median);
  
  return stat;
}
  
std::vector<TargetPtr> MedianRegressionLeafNodeFcn::Eval(
    const SamplePtr sample,
    const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {
  int rows = fcns[0]->stat(0)->rows();
  int cols = fcns[0]->stat(0)->cols();
  RfMatPtr median = CreateRfMatZero(rows, cols);
  
  std::vector<float> values(fcns.size());
  for(int row = 0; row < median->rows(); ++row) {
    for(int col = 0; col < median->cols(); ++col) {
      for(size_t target_idx = 0; target_idx < fcns.size(); ++target_idx) {
        values[target_idx] = (*(fcns[target_idx]->stat(0)))(row, col);
      }
      (*median)(row, col) = rv::stat::Median(values);
    }
  }
  
  TargetPtr target = boost::make_shared<Target>(median);
  return std::vector<TargetPtr>(1, target);
}

} //ns rf
} //ns rv
