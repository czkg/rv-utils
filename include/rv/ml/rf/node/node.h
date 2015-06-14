#ifndef RF_NODE_H
#define RF_NODE_H

#include <fstream>

#include <boost/shared_ptr.hpp>

#include "../proto/rf.pb.h"

#include <rv/io/serialization/serialization.h>

namespace rv {
namespace rf {
    
class Node {
public:
  Node() {}
  virtual ~Node() {}

  virtual boost::shared_ptr<Node> Copy() const = 0;
  
  virtual ForestParameter::NodeType node_type() const = 0;

  virtual void Save(rv::io::SerializationOut& ar) const = 0;
  virtual void Load(rv::io::SerializationIn& ar) = 0;
  
};

typedef boost::shared_ptr<Node> NodePtr;


} //ns rf
} //ns rv

#endif
