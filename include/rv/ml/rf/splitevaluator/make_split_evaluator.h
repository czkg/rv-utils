#ifndef RF_MAKE_SPLIT_EVALUATOR
#define RF_MAKE_SPLIT_EVALUATOR

#include <iostream>
#include <stdexcept>

#include <boost/make_shared.hpp>

#include <rv/log/log.h>

#include <rv/ml/rf/splitevaluator/classificationsplitevaluator.h>
#include <rv/ml/rf/splitevaluator/regressionsplitevaluator.h>
#include <rv/ml/rf/proto/rf.pb.h>

namespace rv {
namespace rf {
  
std::vector<SplitEvaluatorPtr> MakeSplitEvaluator(const ForestParameter& forest_param);
  
}
}

#endif
