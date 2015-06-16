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

#ifndef RF_SPLITNODE_H
#define RF_SPLITNODE_H

#include <rv/ml/rf/node/node.h>
#include <rv/ml/rf/node/make_node.h>
#include <rv/ml/rf/node/leafnode.h>
#include <rv/ml/rf/splitfunction/make_split_function.h>

#include <stdexcept>


namespace rv {
namespace rf {
    
class SplitNode : public Node {    
public:    
  SplitNode() {}
  
  SplitNode(NodePtr left, NodePtr right, SplitFunctionPtr split_fcn) :
    left_(left), right_(right), split_fcn_(split_fcn)
  {}
  
  virtual ~SplitNode() {}
  
  virtual boost::shared_ptr<Node> Copy() const {
    boost::shared_ptr<SplitNode> node = boost::make_shared<SplitNode>();
    node->left_ = left_->Copy();
    node->right_ = right_->Copy();
    node->split_fcn_ = split_fcn_->Copy();

    return node;
  }
  
  bool Split(SamplePtr sample);  
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    int split_fcn_type = split_fcn_->type();
    ar << split_fcn_type;
    split_fcn_->Save(ar);

    //left
    int type = left_->node_type();
    ar << type;
    left_->Save(ar);
        
    //right
    type = right_->node_type();
    ar << type;
    right_->Save(ar);
  }

  virtual void Load(rv::io::SerializationIn& ar) {
    int split_fcn_type;
    ar >> split_fcn_type;
    
    split_fcn_ = MakeSplitFunction(SplitFunctionParameter::SplitFunctionType(split_fcn_type));
    split_fcn_->Load(ar);

    //left
    int left_type;
    ar >> left_type;
    left_ = MakeNode(left_type);
    left_->Load(ar);

    //right
    int right_type;
    ar >> right_type;
    right_ = MakeNode(right_type);
    right_->Load(ar);
  }
  
  
  virtual ForestParameter::NodeType node_type() const { return ForestParameter::SPLIT_NODE; }
  
  NodePtr left() const { return left_; }
  NodePtr right() const { return right_; }
  SplitFunctionPtr split_fcn() const { return split_fcn_; }
  
  void set_left(NodePtr left) { left_ = left; }
  void set_right(NodePtr right) { right_ = right; }
  void set_split_fcn(SplitFunctionPtr split_fcn) { split_fcn_ = split_fcn; }
    
private:
  NodePtr left_;
  NodePtr right_;
  
  SplitFunctionPtr split_fcn_;    
  
DISABLE_COPY_AND_ASSIGN(SplitNode);
};

typedef boost::shared_ptr<SplitNode> SplitNodePtr;

}
}

#endif
