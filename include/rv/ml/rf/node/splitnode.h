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
