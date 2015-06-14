#include <rv/ml/rf/train/traintree.h>

namespace rv {
namespace rf {
 
void TrainTree::SampleSamples(int n, std::vector<int>& indices) {
  indices.resize(n);    

  for(size_t i = 0; i < indices.size(); ++i) {
    indices[i] = i;
  }
  
  //shuffle indices
  for(size_t i = 0; i < indices.size(); ++i) {
    size_t j = rv::rand::Rand<int>::Uniform(0, indices.size());
    size_t tmp = indices[i];
    indices[i] = indices[j];
    indices[j] = tmp;
  }

  if(indices.size() > param_.n_test_samples()) {
    indices.resize(param_.n_test_samples()); 
  }
}


void TrainTree::Split(const SplitFunctionPtr split_function,
    const std::vector<SamplePtr>& samples, std::vector<bool>& splits, 
    int& n_left, int& n_right) {
      
  n_left = 0;
  n_right = 0;

  splits.resize(samples.size());
  for(size_t sample_idx = 0; sample_idx < samples.size(); ++sample_idx) {
    SamplePtr sample = samples[sample_idx];
    splits[sample_idx] = split_function->Split(sample);

    if(splits[sample_idx]) { 
      n_left++;
    }
    else {
      n_right++;
    }
  }
}


SplitFunctionPtr TrainTree::OptimizeSplitFunction(
    const std::vector<SamplePtr>& samples, 
    const std::vector<VecPtrTargetPtr>& optimize_targets) {
 
  std::vector<int> split_indices;
  SampleSamples(samples.size(), split_indices);

  std::vector<SamplePtr> split_samples;
  std::vector<VecPtrTargetPtr> split_optimize_targets(optimize_targets.size());

  SampleSamples(samples, split_indices, split_samples);
  for(size_t idx = 0; idx < optimize_targets.size(); ++idx) {
    split_optimize_targets[idx] = boost::make_shared<VecTargetPtr>();
    SampleSamples(*(optimize_targets[idx]), split_indices, 
      *(split_optimize_targets[idx]));
  }

  int min_samples_for_leaf = param_.min_samples_for_leaf();
  
  float min_cost = 1e6;
  SplitFunctionPtr best_split_fcn;
  float best_threshold;

  std::vector<bool> splits;
  int n_left;
  int n_right;
  
  for(size_t split_fcn_idx = 0; split_fcn_idx < param_.n_test_split_functions(); ++split_fcn_idx) {
    SplitFunctionPtr split_fcn = gen_split_fcn_->Generate();
    
    for(size_t threshold_idx = 0; threshold_idx < param_.n_test_thresholds(); ++threshold_idx) {
      int rand_split_sample_idx = rv::rand::Rand<int>::Uniform(0, split_samples.size());
      float threshold = split_fcn->Compute(split_samples[rand_split_sample_idx]);
      split_fcn->set_threshold(threshold);
     
      Split(split_fcn, split_samples, splits, n_left, n_right);
      if(n_left < min_samples_for_leaf || n_right < min_samples_for_leaf) {
        continue;
      }
                      
      float split_cost = 0;
      for(size_t split_ev_idx = 0; split_ev_idx < split_evaluator_.size(); ++split_ev_idx) {      
        std::vector<TargetPtr> left_targets, right_targets;
        Split(*(split_optimize_targets[split_ev_idx]), splits, left_targets, 
            right_targets);

        SplitEvaluatorPtr split_evaluator = split_evaluator_[split_ev_idx];
        split_cost += split_evaluator->Eval(left_targets, right_targets);
      }

      // std::cout << ", " << split_cost << ", " << threshold << "; " << std::endl;
      
      if(split_cost < min_cost) {
        min_cost = split_cost;
        best_split_fcn = split_fcn;
        best_threshold = threshold; //need theshold extra because of pointer
      }
    }
  }
  
  if(best_split_fcn != 0) {
    best_split_fcn->set_threshold(best_threshold);
  }
  
  return best_split_fcn;

}


NodePtr TrainTree::CreateLeafNode(const std::vector<SamplePtr>& samples, 
    const std::vector<VecPtrTargetPtr>& targets, int depth) {
  
  size_t n_fcns = gen_leaf_node_fcns_.size();
  std::vector<LeafNodeFcnPtr> leaf_node_fcns(n_fcns);
  for(size_t fcn_idx = 0; fcn_idx < n_fcns; ++fcn_idx) {
    VecPtrTargetPtr fcn_targets = targets[fcn_idx];
    leaf_node_fcns[fcn_idx] = gen_leaf_node_fcns_[fcn_idx]->Create(
      param_.leaf_node_fcn_param(fcn_idx), samples, *(fcn_targets));
  }

  LeafNodePtr node = boost::make_shared<LeafNode>(leaf_node_fcns);
  
  CreatedNodeInfo(depth, true);
  
  return node;
}


} //ns rf
} //ns rv
