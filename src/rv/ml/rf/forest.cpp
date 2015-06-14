#include <rv/ml/rf/forest.h>


namespace rv {
namespace rf {

VecPtrTargetPtr Forest::inferencemt(const SamplePtr& sample) const {
  int n_trees = trees_.size();

  std::vector<std::vector<LeafNodeFcnPtr> > fcns(n_leaf_node_fcns_, 
      std::vector<LeafNodeFcnPtr>(n_trees));
  
  //inference of individual trees
  #pragma omp parallel for
  for(int tree_idx = 0; tree_idx < n_trees; ++tree_idx) {
    std::vector<LeafNodeFcnPtr> tree_fcns = trees_[tree_idx]->inference(sample);
    
    for(int fcn_idx = 0; fcn_idx < n_leaf_node_fcns_; ++fcn_idx) {
      fcns[fcn_idx][tree_idx] = tree_fcns[fcn_idx];
    }
  }
  
  //combine tree fcns/results and collect all results
  VecPtrTargetPtr targets = boost::make_shared<VecTargetPtr>();
  for(int fcn_idx = 0; fcn_idx < n_leaf_node_fcns_; ++fcn_idx) {
    VecTargetPtr fcn_targets = fcns[fcn_idx][0]->Eval(sample, fcns[fcn_idx]);

    for(size_t target_idx = 0; target_idx < fcn_targets.size(); ++target_idx) {
      (*targets).push_back(fcn_targets[target_idx]);
    }
  }

  return targets;
}

VecPtrTargetPtr Forest::inferencest(const SamplePtr& sample) const {
  int n_trees = trees_.size();

  std::vector<std::vector<LeafNodeFcnPtr> > fcns(n_leaf_node_fcns_, 
      std::vector<LeafNodeFcnPtr>(n_trees));
  
  //inference of individual trees
  for(int tree_idx = 0; tree_idx < n_trees; ++tree_idx) {
    std::vector<LeafNodeFcnPtr> tree_fcns = trees_[tree_idx]->inference(sample);
    
    for(int fcn_idx = 0; fcn_idx < n_leaf_node_fcns_; ++fcn_idx) {
      fcns[fcn_idx][tree_idx] = tree_fcns[fcn_idx];
    }
  }
  
  //combine tree fcns/results and collect all results
  VecPtrTargetPtr targets = boost::make_shared<VecTargetPtr>();
  for(int fcn_idx = 0; fcn_idx < n_leaf_node_fcns_; ++fcn_idx) {
    VecTargetPtr fcn_targets = fcns[fcn_idx][0]->Eval(sample, fcns[fcn_idx]);

    for(size_t target_idx = 0; target_idx < fcn_targets.size(); ++target_idx) {
      (*targets).push_back(fcn_targets[target_idx]);
    }
  }

  return targets;
}
  
std::vector<VecPtrTargetPtr> Forest::inferencemt(const std::vector<SamplePtr>& samples) const {
  std::vector<VecPtrTargetPtr> targets(samples.size());

  #pragma omp parallel for
  for(size_t sample_idx = 0; sample_idx < samples.size(); ++sample_idx) {
    targets[sample_idx] = inferencest(samples[sample_idx]);
  }

  return targets;
}

std::vector<VecPtrTargetPtr> Forest::inferencest(const std::vector<SamplePtr>& samples) const {
  std::vector<VecPtrTargetPtr> targets(samples.size());

  for(size_t sample_idx = 0; sample_idx < samples.size(); ++sample_idx) {
    targets[sample_idx] = inferencest(samples[sample_idx]);
  }

  return targets;
}

} // ns rf
} // ns rv

