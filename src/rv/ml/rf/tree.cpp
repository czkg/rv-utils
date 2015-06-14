#include <rv/ml/rf/tree.h>

namespace rv {
namespace rf {

std::vector<LeafNodeFcnPtr> Tree::inference(const SamplePtr sample) const {
  if(root_ == 0) {
    LOG_ERROR << "tree inference root node is NULL";
  }
  
  NodePtr node = root_;
  while(node->node_type() == ForestParameter::SPLIT_NODE) {
    SplitNodePtr splitNode = boost::static_pointer_cast<SplitNode>(node);
    bool left = splitNode->Split(sample);
    if(left) {
      node = splitNode->left();
    }
    else {
      node = splitNode->right();
    }
  }
  
  LeafNodePtr leaf_node = boost::static_pointer_cast<LeafNode>(node);
  return leaf_node->leaf_node_fcns();
}

} //ns rf 
} //ns rv
