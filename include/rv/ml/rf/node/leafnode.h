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
