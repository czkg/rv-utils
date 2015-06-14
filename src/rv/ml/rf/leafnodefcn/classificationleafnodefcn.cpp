#include <rv/ml/rf/leafnodefcn/classificationleafnodefcn.h>

namespace rv {
namespace rf {

boost::shared_ptr<LeafNodeFcn> ClassificationLeafNodeFcn::Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const std::vector<TargetPtr>& targets) const {
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMatPtr probs = CreateRfMatZero(rows, cols);
  
  double sum = 0;
  for(size_t tidx = 0; tidx < targets.size(); ++tidx) {
    RfMatPtr data = targets[tidx]->data();
    *probs = (*probs) + (*data);
    sum += data->sum();
  }
  *probs = (*probs) * (1.0 / sum);
  
  LeafNodeFcnPtr stat = boost::make_shared<ClassificationLeafNodeFcn>();
  stat->add_stat(probs);
  
  return stat;
}

std::vector<TargetPtr> ClassificationLeafNodeFcn::Eval(
    const SamplePtr sample,
    const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {
  int rows = fcns[0]->stat(0)->rows();
  int cols = fcns[0]->stat(0)->cols();
  RfMatPtr probs = CreateRfMatZero(rows, cols);
  
  for(size_t idx = 0; idx < fcns.size(); ++idx) {
    *probs = (*probs) + (*(fcns[idx]->stat(0)));
  }
  
  *probs = (*probs) * (1.0 / fcns.size());
  
  TargetPtr target = boost::make_shared<Target>(probs);
  return std::vector<TargetPtr>(1, target);
}


} //ns rf
} //ns rv
