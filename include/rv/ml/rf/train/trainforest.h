#ifndef RF_TRAINFOREST_H
#define RF_TRAINFOREST_H

#include <rv/ml/rf/forest.h>
#include <rv/ml/rf/train/traintreerecursive.h>
#include <rv/ml/rf/splitevaluator/make_split_evaluator.h>

namespace rv {
namespace rf {
    
class TrainForest {
public:
  TrainForest(const ForestParameter& param, bool verbose) : 
      param_(param), verbose_(verbose) {
    gen_split_fcn_ = MakeSplitFunction(param.split_function_param().type());
    
    int n_leaf_node_fcns = param.leaf_node_fcn_param_size();
    gen_leaf_node_fcns_.resize(n_leaf_node_fcns);
    for(int fcn_idx = 0; fcn_idx < n_leaf_node_fcns; ++fcn_idx) {
      gen_leaf_node_fcns_[fcn_idx] = MakeLeafNodeFcn(param.leaf_node_fcn_param(fcn_idx).type());
    }
    
    split_evaluator_ = MakeSplitEvaluator(param);
  }
  
  virtual ~TrainForest() {}

  virtual boost::shared_ptr<Forest> Train(std::vector<SamplePtr>& samples,
      std::vector<VecPtrTargetPtr>& targets, 
      std::vector<VecPtrTargetPtr>& optimize_targets,
      TrainType train_type, const boost::shared_ptr<Forest>& old_forest);
    

private:    
  const ForestParameter& param_;
  SplitFunctionPtr gen_split_fcn_; 
  std::vector<LeafNodeFcnPtr> gen_leaf_node_fcns_; 
  std::vector<SplitEvaluatorPtr> split_evaluator_;
  
  bool verbose_;
};
    
}
}

#endif
