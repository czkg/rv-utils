#include <rv/ml/rf/train/traintreerecursive.h>

namespace rv {
namespace rf {

TreePtr TrainTreeRecursive::Train(std::vector<SamplePtr>& samples, 
      std::vector<VecPtrTargetPtr>& targets, 
      std::vector<VecPtrTargetPtr>& optimize_targets, 
      TrainType train_type, const TreePtr& old_tree) {
  NodePtr old_root;
  if(old_tree != 0) {
    old_root = old_tree->root();
  }

  NodePtr root = Train(samples, targets, optimize_targets, train_type, old_root, 0);
  return boost::make_shared<Tree>(root);
}


NodePtr TrainTreeRecursive::Train(std::vector<SamplePtr>& samples, 
      std::vector<VecPtrTargetPtr>& targets, 
      std::vector<VecPtrTargetPtr>& optimize_targets, 
      TrainType train_type, const NodePtr& old_node, int depth) {
  
  if(depth < param_.max_tree_depth() && samples.size() > param_.min_samples_to_split()) {
    SplitFunctionPtr best_split_fcn; 
    bool was_split_node = false;
    if(old_node == 0 || old_node->node_type() == ForestParameter::LEAF_NODE) {
      best_split_fcn = OptimizeSplitFunction(samples, optimize_targets);
      was_split_node = false;
    }
    else if(old_node->node_type() == ForestParameter::SPLIT_NODE) {
      SplitNodePtr split_node = boost::static_pointer_cast<SplitNode>(old_node);
      best_split_fcn = split_node->split_fcn()->Copy();
      was_split_node = true;
    }
    
    if(best_split_fcn == 0) { 
      if(old_node == 0 || train_type == TRAIN || train_type == RETRAIN_WITH_REPLACEMENT) {
        return CreateLeafNode(samples, targets, depth);
      }
      else if(train_type == RETRAIN) {
        return old_node->Copy();
      }
      else {
        LOG_ERROR << "unknown train type";
      }
    }
            
    //split samples, targets, optimization targets
    // (1) determine splits
    std::vector<bool> splits;
    int n_left, n_right;
    Split(best_split_fcn, samples, splits, n_left, n_right);

    // (2) split samples
    std::vector<SamplePtr> leftsamples, rightsamples;
    Split(samples, splits, leftsamples, rightsamples);
    
    // (3) split targets
    std::vector<VecPtrTargetPtr> left_targets(targets.size());
    std::vector<VecPtrTargetPtr> right_targets(targets.size());
    for(size_t idx = 0; idx < targets.size(); ++idx) {
      left_targets[idx] = boost::make_shared<VecTargetPtr>();
      right_targets[idx] = boost::make_shared<VecTargetPtr>();
      Split(*(targets[idx]), splits, *(left_targets[idx]), *(right_targets[idx]));
    }
    
    // (4) split optimization targets
    std::vector<VecPtrTargetPtr> left_optimize_targets(optimize_targets.size());
    std::vector<VecPtrTargetPtr> right_optimize_targets(optimize_targets.size());
    for(size_t idx = 0; idx < optimize_targets.size(); ++idx) {
      left_optimize_targets[idx] = boost::make_shared<VecTargetPtr>();
      right_optimize_targets[idx] = boost::make_shared<VecTargetPtr>();
      Split(*(optimize_targets[idx]), splits, 
          *(left_optimize_targets[idx]), *(right_optimize_targets[idx]));
    }
    
    //output node information
    CreatedNodeInfo(depth, false);
    
    //create split node - recursively train the siblings
    if(was_split_node) {
      SplitNodePtr split_node = boost::static_pointer_cast<SplitNode>(old_node);
      NodePtr left = Train(leftsamples, left_targets, left_optimize_targets, train_type, split_node->left(), depth + 1);
      NodePtr right = Train(rightsamples, right_targets, right_optimize_targets, train_type, split_node->right(), depth + 1);
      SplitNodePtr new_node = boost::make_shared<SplitNode>(left, right, best_split_fcn);
      return new_node;
    }
    else {
      NodePtr null_node;
      NodePtr left = Train(leftsamples, left_targets, left_optimize_targets, train_type, null_node, depth + 1);
      NodePtr right = Train(rightsamples, right_targets, right_optimize_targets, train_type, null_node, depth + 1);
      SplitNodePtr new_node = boost::make_shared<SplitNode>(left, right, best_split_fcn);
      return new_node;
    }
  } //if samples < min_samples || depth >= max_depth
  else {
    if(old_node == 0 || train_type == TRAIN || train_type == RETRAIN_WITH_REPLACEMENT) {
      return CreateLeafNode(samples, targets, depth);
    }
    else if(train_type == RETRAIN) {
      return old_node->Copy();
    }
    else {
      LOG_ERROR << "unknown train type";
    }
  }

}

} //ns rf
} //ns rf
