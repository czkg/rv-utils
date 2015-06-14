#include <rv/ml/rf/leafnodefcn/make_leaf_node_fcn.h>

rv::rf::LeafNodeFcnPtr rv::rf::MakeLeafNodeFcn(rv::rf::LeafNodeFcnParameter::LeafNodeFcnType type) {
  if(type == LeafNodeFcnParameter::CLASSIFICATION) {
    return boost::make_shared<ClassificationLeafNodeFcn>();
  }
  else if(type == LeafNodeFcnParameter::REGRESSION_MEAN) {
    return boost::make_shared<MeanRegressionLeafNodeFcn>();
  }
  else if(type == LeafNodeFcnParameter::REGRESSION_MEAN_STD) {
    return boost::make_shared<MeanStdRegressionLeafNodeFcn>();
  }
  else if(type == LeafNodeFcnParameter::REGRESSION_MEDIAN) {
    return boost::make_shared<MedianRegressionLeafNodeFcn>();
  }
  else if(type == LeafNodeFcnParameter::REGRESSION_REGRESSION) {
    return boost::make_shared<RegressionRegressionLeafNodeFcn>();
  }
  else {
    LOG_ERROR << "unknown leaf node fcn: " << type;
  }
}
