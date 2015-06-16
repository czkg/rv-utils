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

#ifndef RF_TRAINTREE_H
#define RF_TRAINTREE_H

#include <rv/ml/rf/splitevaluator/splitevaluator.h>
#include <rv/ml/rf/leafnodefcn/make_leaf_node_fcn.h>
#include <rv/ml/rf/tree.h>
#include <rv/ml/rf/proto/rf.pb.h>

#include <rv/rand/rand.h>

#include <boost/make_shared.hpp>
#include <boost/format.hpp>

namespace rv {
namespace rf {   

enum TrainType {
  TRAIN = 0,
  RETRAIN = 1,
  RETRAIN_WITH_REPLACEMENT = 2,
};

class TrainTree {    
public:
  TrainTree(int id, const ForestParameter& param, 
      const SplitFunctionPtr gen_split_fcn, 
      const std::vector<LeafNodeFcnPtr> gen_leaf_node_fcns,
      const std::vector<SplitEvaluatorPtr>& split_evaluator,
      bool verbose) : 
    id_(id), param_(param), gen_split_fcn_(gen_split_fcn), 
    gen_leaf_node_fcns_(gen_leaf_node_fcns), 
    split_evaluator_(split_evaluator), verbose_(verbose) {
    
    n_created_nodes_ = 0;
    n_max_nodes_ = 1;
    unsigned long n_nodes_d = 1;
    for(unsigned int depth = 0; depth < param.max_tree_depth(); ++depth) {
      n_nodes_d *= 2;
      n_max_nodes_ += n_nodes_d;
    }
  }
  
  virtual ~TrainTree() {}
      
  virtual TreePtr Train(std::vector<SamplePtr>& samples, 
      std::vector<VecPtrTargetPtr>& targets, std::vector<VecPtrTargetPtr>& optimize_targets, 
      TrainType train_type, const TreePtr& old_tree) = 0;

protected:    
  virtual void CreatedNodeInfo(unsigned int depth, bool leaf) {
    if(verbose_) {
      n_created_nodes_ += 1;
     
      if(leaf) {
        unsigned long n_nodes_d = 1;
        unsigned int n_remove_max_nodes = 0;
        for(unsigned int d = depth; d < param_.max_tree_depth(); ++d) {
          n_nodes_d *= 2;
          n_remove_max_nodes += n_nodes_d;
        }
        n_max_nodes_ -= n_remove_max_nodes;
      }
      
      if(n_created_nodes_ % 250 == 0 || n_created_nodes_ == n_max_nodes_) {
        LOG_INFO << "[TREE_" << id_ << "]" 
          << " created node number " << n_created_nodes_ 
          << " @ depth " << depth 
          << ", max. " << n_max_nodes_ << " left" 
          << " => " << (double(n_created_nodes_) / double(n_max_nodes_)) 
          << " done";
      }
    }
  }

  virtual void SampleSamples(int n, std::vector<int>& indices);

  template <typename T>
  void SampleSamples(const std::vector<T>& all, 
      const std::vector<int>& indices, std::vector<T>& sampled) {
    sampled.resize(indices.size());
    for(size_t idx = 0; idx < indices.size(); ++idx) {
      sampled[idx] = all[indices[idx]];
    }
  }
  
  virtual void Split(const SplitFunctionPtr split_function,
    const std::vector<SamplePtr>& samples,
    std::vector<bool>& splits, int& n_left, int& n_right);


  template <typename T>
  void Split(const std::vector<T>& all, const std::vector<bool>& splits,
      std::vector<T>& left, std::vector<T>& right) {
    for(size_t idx = 0; idx < all.size(); ++idx) {
      T t = all[idx];
      if(splits[idx]) {
        left.push_back(t);
      }
      else {
        right.push_back(t);
      }
    }
  }

  
  virtual SplitFunctionPtr OptimizeSplitFunction(
      const std::vector<SamplePtr>& samples, 
      const std::vector<VecPtrTargetPtr>& optimize_targets);
  
  
  virtual NodePtr CreateLeafNode(const std::vector<SamplePtr>& samples, 
      const std::vector<VecPtrTargetPtr>& targets, int depth);
            
protected:
  const int id_;
  
  const ForestParameter& param_;
  const SplitFunctionPtr gen_split_fcn_;
  const std::vector<LeafNodeFcnPtr> gen_leaf_node_fcns_;
  const std::vector<SplitEvaluatorPtr>& split_evaluator_;
  
  bool verbose_;
  unsigned long n_created_nodes_;
  unsigned long n_max_nodes_;
};

typedef boost::shared_ptr<TrainTree> TrainTreePtr;

} //ns rf
} //ns rv

#endif
