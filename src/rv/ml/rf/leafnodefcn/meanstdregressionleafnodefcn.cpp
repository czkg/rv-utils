#include <rv/ml/rf/leafnodefcn/regressionleafnodefcn.h>

namespace rv {
namespace rf {

LeafNodeFcnPtr MeanStdRegressionLeafNodeFcn::Create(
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
 
  RfMatPtr var = CreateRfMatZero(rows, cols);
  if(targets.size() > 1) {
    for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
      RfMat val = (*(targets[target_idx]->data())) - (*mean);
      *var = (*var) + val.array().square().matrix();
    }
    *var = (*var) * (1.0 / float(targets.size() - 1));
  }
  else {
    std::cout << "[WARNING] number of targets = " << targets.size() 
      << " for variance computation - setting to -1" << std::endl;
    var->setConstant(-1);
  }
  
  LeafNodeFcnPtr stat = boost::make_shared<MeanStdRegressionLeafNodeFcn>();
  stat->add_stat(mean);
  stat->add_stat(var);
  
  return stat;
}
  
std::vector<TargetPtr> MeanStdRegressionLeafNodeFcn::Eval(
    const SamplePtr sample,
    const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {
  int rows = fcns[0]->stat(0)->rows();
  int cols = fcns[0]->stat(0)->cols();
  RfMatPtr mean = CreateRfMatZero(rows, cols);

  for(size_t i = 0; i < fcns.size(); ++i) {
    *mean = (*mean) + (*(fcns[i]->stat(0)));
  }
  *mean = (*mean) * (1.0 / float(fcns.size()));
  
 
  RfMatPtr var = CreateRfMatZero(rows, cols);
  for(size_t i = 0; i < fcns.size(); ++i) {
    *var = (*var) + (*(fcns[i]->stat(1)));
  }
  *var = (*var) * (1.0 / float(fcns.size()));
  
  TargetPtr target_mean = boost::make_shared<Target>(mean);
  TargetPtr target_var = boost::make_shared<Target>(var);
  
  std::vector<TargetPtr> target(2);
  target[0] = target_mean;
  target[1] = target_var;

  return target;
}


} //ns rf
} //ns rv
