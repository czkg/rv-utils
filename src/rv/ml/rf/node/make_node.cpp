#include <rv/ml/rf/node/make_node.h>
#include <rv/ml/rf/node/splitnode.h>
#include <rv/ml/rf/node/leafnode.h>

namespace rv {
namespace rf {

NodePtr MakeNode(int type) {
  NodePtr node;
  if(type == ForestParameter::LEAF_NODE) {
    node = boost::make_shared<LeafNode>();
  }
  else if(type == ForestParameter::SPLIT_NODE) {
    node = boost::make_shared<SplitNode>();
  }
  else {
    LOG_ERROR << "unknown node type: " << type;
  }

  return node;
}


} //ns rf
} //ns rv
