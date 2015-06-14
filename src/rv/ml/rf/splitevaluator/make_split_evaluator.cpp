#include <rv/ml/rf/splitevaluator/make_split_evaluator.h>

namespace rv {
namespace rf {

std::vector<SplitEvaluatorPtr> MakeSplitEvaluator(
    const ForestParameter& forest_param) {

  int n_split_evaluator = forest_param.split_evaluator_param_size();
  if(n_split_evaluator == 0) {
    LOG_ERROR << "at least one split evaluator has to be defined";
  }

  std::vector<SplitEvaluatorPtr> split_evaluators(n_split_evaluator);

  for(int idx = 0; idx < n_split_evaluator; ++idx) {
    const SplitEvaluatorParameter& param = forest_param.split_evaluator_param(idx);

    bool normalize = param.normalize();
    float weight = param.weight();

    SplitEvaluatorPtr split_evaluator;

    if(param.type() == SplitEvaluatorParameter::CLASSIFICATION_INFORMATION_GAIN) {
      std::cout << "[INFO] make split evaluator: CLASSIFICATION_INFORMATION_GAIN" << std::endl;
      split_evaluator =  boost::make_shared<InformationGainClassificationSplitEvaluator>(normalize, weight);
    }
    else if(param.type() == SplitEvaluatorParameter::CLASSIFICATION_GINI) {
      std::cout << "[INFO] make split evaluator: CLASSIFICATION_GINI" << std::endl;
      split_evaluator =  boost::make_shared<GiniClassificationSplitEvaluator>(normalize, weight);
    }
    else if(param.type() == SplitEvaluatorParameter::REGRESSION_TRACE_COV) {
      std::cout << "[INFO] make split evaluator: REGRESSION_TRACE_COV" << std::endl;
      split_evaluator =  boost::make_shared<TraceCovRegressionSplitEvaluator>(normalize, weight);
    }
    else if(param.type() == SplitEvaluatorParameter::REGRESSION_WEIGHTED_TRACE_COV) {
      std::cout << "[INFO] make split evaluator: REGRESSION_WEIGHTED_TRACE_COV" << std::endl;
      bool weighted_mean = param.weighted_mean();
      split_evaluator =  boost::make_shared<WeightedTraceCovRegressionSplitEvaluator>(normalize, weight, weighted_mean);
    }
    else if(param.type() == SplitEvaluatorParameter::REGRESSION_VARIANCE_REDUCTION) {
      std::cout << "[INFO] make split evaluator: REGRESSION_VARIANCE_REDUCTION" << std::endl;
      split_evaluator =  boost::make_shared<VarianceReductionRegressionSplitEvaluator>(normalize, weight);
    }
    else {
      LOG_ERROR << "unknown split evaluator";
    }

    split_evaluators[idx] = split_evaluator;
  }

  return split_evaluators;
}


} //ns rf 
} //ns rv
