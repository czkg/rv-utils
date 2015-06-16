// Copyright (C) 2015 Institute for Computer Graphics and Vision (ICG),
//   Graz University of Technology (TU GRAZ)

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the ICG, TU GRAZ.
// 4. Neither the name of the ICG, TU GRAZ nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY ICG, TU GRAZ ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ICG, TU GRAZ BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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

