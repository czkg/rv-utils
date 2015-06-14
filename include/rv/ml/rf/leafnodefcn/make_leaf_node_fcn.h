#ifndef RF_MAKE_LEAF_NODE_STAT_HPP
#define RF_MAKE_LEAF_NODE_STAT_HPP

#include <rv/ml/rf/proto/rf.pb.h>
#include <rv/ml/rf/leafnodefcn/classificationleafnodefcn.h>
#include <rv/ml/rf/leafnodefcn/regressionleafnodefcn.h>

#include <rv/log/log.h>

namespace rv {
namespace rf {
  
LeafNodeFcnPtr MakeLeafNodeFcn(LeafNodeFcnParameter::LeafNodeFcnType type);
  
}  
}

#endif
