#include <rv/ml/rf/leafnodefcn/regressionleafnodefcn.h>

namespace rv {
namespace rf {

LeafNodeFcnPtr MeanRegressionLeafNodeFcn::Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const std::vector<TargetPtr>& targets) const {
  
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMatPtr mean = CreateRfMatZero(rows, cols);

  for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
    *mean = (*mean) + (*(targets[target_idx]->data()));
  }
  *mean = (*mean) * (1.0 / double(targets.size()));
  
  LeafNodeFcnPtr stat = boost::make_shared<MeanRegressionLeafNodeFcn>();
  stat->add_stat(mean);
  
  return stat;
}
  
std::vector<TargetPtr> MeanRegressionLeafNodeFcn::Eval(const SamplePtr sample,
      const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {

  int rows = fcns[0]->stat(0)->rows();
  int cols = fcns[0]->stat(0)->cols();
  RfMatPtr mean = CreateRfMatZero(rows, cols);

  for(size_t i = 0; i < fcns.size(); ++i) {
    *mean = (*mean) + (*(fcns[i]->stat(0)));
  }
  *mean = (*mean) * (1.0 / float(fcns.size()));
  
  TargetPtr target = boost::make_shared<Target>(mean);
  return std::vector<TargetPtr>(1, target);
}

} //ns rf
} //ns rv
