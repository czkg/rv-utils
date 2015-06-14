#ifndef RF_TRAINTREERECURSIVE_H
#define RF_TRAINTREERECURSIVE_H

#include <rv/ml/rf/train/traintree.h>


namespace rv {
namespace rf {

class TrainTreeRecursive : public TrainTree {
public:
  TrainTreeRecursive(int id, const ForestParameter& param, 
      const SplitFunctionPtr gen_split_fcn, 
      const std::vector<LeafNodeFcnPtr> gen_leaf_node_fcns,
      const std::vector<SplitEvaluatorPtr>& split_evaluator, bool verbose) : 
    TrainTree(id, param, gen_split_fcn, gen_leaf_node_fcns, split_evaluator, 
        verbose) 
  {}
  
  virtual ~TrainTreeRecursive() {}
  
  virtual TreePtr Train(std::vector<SamplePtr>& samples, 
      std::vector<VecPtrTargetPtr>& targets, 
      std::vector<VecPtrTargetPtr>& optimize_targets, 
      TrainType train_type, const TreePtr& old_tree);
          
protected:    
                  
  virtual NodePtr Train(std::vector<SamplePtr>& samples, 
      std::vector<VecPtrTargetPtr>& targets,
      std::vector<VecPtrTargetPtr>& optimize_targets, 
      TrainType train_type, const NodePtr& old_node, int depth);

};


}
}


#endif
