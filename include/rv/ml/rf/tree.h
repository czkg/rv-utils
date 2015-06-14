#ifndef RV_RF_TREE_H
#define RV_RF_TREE_H

#include <rv/ml/rf/node/splitnode.h>
#include <rv/ml/rf/node/leafnode.h>
#include <rv/ml/rf/node/make_node.h>

#include <rv/io/serialization/serialization.h>

#include <stdexcept>

namespace rv {
namespace rf {
    
    
class Tree {    
public:
  Tree() {}
  Tree(NodePtr root) : root_(root) {}
  
  virtual ~Tree() {}
  
  std::vector<LeafNodeFcnPtr> inference(const SamplePtr sample) const;
  
  NodePtr root() const { return root_; }
  void set_root(NodePtr root) { root_ = root; }
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    int type = root_->node_type();
    ar << type;
    root_->Save(ar);
  }
  
  virtual void Load(rv::io::SerializationIn& ar) {
    int type;
    ar >> type;
    root_ = MakeNode(type);
    root_->Load(ar);
  }
    
    
private:
  NodePtr root_;
};

typedef boost::shared_ptr<Tree> TreePtr;

}
}

#endif
