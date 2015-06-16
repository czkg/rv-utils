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

#ifndef RV_RF_FOREST_H
#define RV_RF_FOREST_H

#include <vector>
#include <iostream>

#include <boost/make_shared.hpp>
#include <boost/format.hpp>

#include <rv/log/log.h>
#include <rv/io/serialization/serialization.h>
#include <rv/ml/rf/tree.h>


namespace rv {
namespace rf {

class Target;
    
class Forest {    
public:
  Forest() {}
  virtual ~Forest() {}
  
  VecPtrTargetPtr inferencemt(const SamplePtr& sample) const;  
  VecPtrTargetPtr inferencest(const SamplePtr& sample) const;

  std::vector<VecPtrTargetPtr> inferencemt(const std::vector<SamplePtr>& samples) const;  
  std::vector<VecPtrTargetPtr> inferencest(const std::vector<SamplePtr>& samples) const;
  
  
  void AddTree(TreePtr tree) { 
    trees_.push_back(tree); 
  }
  
  size_t trees_size() const { return trees_.size(); }
  TreePtr trees(int idx) const { return trees_[idx]; }

  int n_leaf_node_fcns() const { return n_leaf_node_fcns_; }
  void set_n_leaf_node_fcns(int n_leaf_node_fcns) { n_leaf_node_fcns_ = n_leaf_node_fcns; }
  
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    size_t n_trees = trees_.size();
    std::cout << "[DEBUG] write " << n_trees << " trees" << std::endl;
    ar << n_trees;

    if(true) std::cout << "[Forest][write] write number of trees " << n_trees << std::endl;

    for(size_t tree_idx = 0; tree_idx < trees_.size(); ++tree_idx) {
      if(true) std::cout << "[Forest][write] write tree nb. " << tree_idx << std::endl;
      trees_[tree_idx]->Save(ar);
    }
    
    ar << n_leaf_node_fcns_;
  }

  virtual void Load(rv::io::SerializationIn& ar) {
    size_t n_trees;
    ar >> n_trees;
    
    if(true) std::cout << "[Forest][read] nTrees: " << n_trees << std::endl;
    
    trees_.clear();
    for(size_t i = 0; i < n_trees; ++i) {
      if(true) std::cout << "[Forest][read] read tree " << (i+1) << " of " << n_trees << " - " << std::endl;
      
      TreePtr tree = boost::make_shared<Tree>();
      tree->Load(ar);
      trees_.push_back(tree);
      
      if(true) std::cout << "[Forest][read] finished read tree " << (i+1) << " of " << n_trees << std::endl;
    }

    ar >> n_leaf_node_fcns_;
  }

    
private:
  std::vector<TreePtr> trees_;
  int n_leaf_node_fcns_;
};

typedef boost::shared_ptr<Forest> ForestPtr;

}
}

#endif
