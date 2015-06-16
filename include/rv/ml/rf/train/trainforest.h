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
