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

#ifndef RV_RF_LEAFNODE_H
#define RV_RF_LEAFNODE_H

#include <rv/ml/rf/node/node.h>
#include <rv/ml/rf/leafnodefcn/make_leaf_node_fcn.h>

#include <vector>
#include <boost/make_shared.hpp>

namespace rv {
namespace rf {
    
class LeafNode : public Node {    
public:
  LeafNode() {}
  LeafNode(std::vector<LeafNodeFcnPtr>  leaf_node_fcns) : 
    leaf_node_fcns_(leaf_node_fcns) 
  { }
  
  virtual ~LeafNode() {}
    
  virtual boost::shared_ptr<Node> Copy() const {
    boost::shared_ptr<LeafNode> node = boost::make_shared<LeafNode>();
    node->leaf_node_fcns_.resize(leaf_node_fcns_.size());
    for(size_t fcn_idx = 0; fcn_idx < leaf_node_fcns_.size(); ++fcn_idx) {
      node->leaf_node_fcns_[fcn_idx] = leaf_node_fcns_[fcn_idx]->Copy();
    }
    return node;
  }



  virtual void Save(rv::io::SerializationOut& ar) const {
    int n_fcns = leaf_node_fcns_.size();
    ar << n_fcns;

    for(int fcn_idx = 0; fcn_idx < n_fcns; ++fcn_idx) {
      int type = leaf_node_fcns_[fcn_idx]->type();
      ar << type;
      leaf_node_fcns_[fcn_idx]->Save(ar);
    }
  }

  virtual void Load(rv::io::SerializationIn& ar) {
    int n_fcns;
    ar >> n_fcns;

    leaf_node_fcns_.resize(n_fcns);
    for(int fcn_idx = 0; fcn_idx < n_fcns; ++fcn_idx) {
      int type;
      ar >> type;

      leaf_node_fcns_[fcn_idx] = MakeLeafNodeFcn(LeafNodeFcnParameter::LeafNodeFcnType(type));
      leaf_node_fcns_[fcn_idx]->Load(ar);
    }
  }
  
  virtual ForestParameter::NodeType node_type() const { return ForestParameter::LEAF_NODE; };
  std::vector<LeafNodeFcnPtr> leaf_node_fcns() const { return leaf_node_fcns_; }
    
private:
  std::vector<LeafNodeFcnPtr> leaf_node_fcns_;
  
DISABLE_COPY_AND_ASSIGN(LeafNode);
};

typedef boost::shared_ptr<LeafNode> LeafNodePtr;

}
}

#endif
