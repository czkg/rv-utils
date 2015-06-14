#ifndef RF_TRAINTREEQUEUED_H
#define RF_TRAINTREEQUEUED_H

#include <rv/ml/rf/train/traintree.h>

#include <queue>

namespace rv {
namespace rf {
    
class TrainTreeQueued : public TrainTree {
public:
  TrainTreeQueued(int id,
            const ForestParameter& param, 
            const SplitFunctionPtr gen_split_fcn, 
            const LeafNodeStatPtr gen_leaf_node_stat,
            const SplitEvaluatorPtr split_evaluator,
            bool verbose) : 
      TrainTree(id, param, gen_split_fcn, gen_leaf_node_stat, split_evaluator, verbose) 
  {}
  
  virtual ~TrainTreeQueued() {}
  
  virtual TreePtr Train(std::vector<SamplePtr>& samples,
                        std::vector<TargetPtr>& targets);
    
};


}
}


#endif
