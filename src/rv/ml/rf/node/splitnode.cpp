#include <rv/ml/rf/node/splitnode.h>

namespace rv {
namespace rf {

bool SplitNode::Split(SamplePtr sample) {
  return split_fcn_->Split(sample);
}


} //ns rf 
} //ns rv
