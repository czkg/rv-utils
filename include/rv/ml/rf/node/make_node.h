#ifndef RV_RF_MAKE_NODE_H
#define RV_RF_MAKE_NODE_H

#include <boost/make_shared.hpp>

#include <rv/ml/rf/proto/rf.pb.h>
#include <rv/ml/rf/node/node.h>

#include <rv/log/log.h>

namespace rv {
namespace rf {
  
NodePtr MakeNode(int type);

} //ns rf  
} //ns rv

#endif
