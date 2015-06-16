// Copyright (C) 2015 Institute for Computer Graphics and Vision (ICG),
//   Graz University of Technology (TU GRAZ)

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the ICG, TU GRAZ.
// 4. Neither the name of the ICG, TU GRAZ nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY ICG, TU GRAZ ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ICG, TU GRAZ BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
