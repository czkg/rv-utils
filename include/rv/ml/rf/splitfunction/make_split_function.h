#ifndef RF_MAKE_SPLIT_FUNCTION
#define RF_MAKE_SPLIT_FUNCTION

#include <rv/log/log.h>

#include <rv/ml/rf/proto/rf.pb.h>

#include <rv/ml/rf/splitfunction/splitfunction.h>

namespace rv {
namespace rf {
  
SplitFunctionPtr MakeSplitFunction(SplitFunctionParameter::SplitFunctionType type);
  
}
}

#endif
