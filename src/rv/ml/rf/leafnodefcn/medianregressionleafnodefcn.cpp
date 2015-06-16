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

#include <rv/ml/rf/leafnodefcn/regressionleafnodefcn.h>

namespace rv {
namespace rf {

LeafNodeFcnPtr MedianRegressionLeafNodeFcn::Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const std::vector<TargetPtr>& targets) const {
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMatPtr median = CreateRfMatZero(rows, cols);
  
  std::vector<float> values(targets.size());
  for(int row = 0; row < median->rows(); ++row) {
    for(int col = 0; col < median->cols(); ++col) {
      for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
        values[target_idx] = (*(targets[target_idx]->data()))(row, col);
      }
      (*median)(row, col) = rv::stat::Median(values);
    }
  }
  
  LeafNodeFcnPtr stat = boost::make_shared<MedianRegressionLeafNodeFcn>();
  stat->add_stat(median);
  
  return stat;
}
  
std::vector<TargetPtr> MedianRegressionLeafNodeFcn::Eval(
    const SamplePtr sample,
    const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {
  int rows = fcns[0]->stat(0)->rows();
  int cols = fcns[0]->stat(0)->cols();
  RfMatPtr median = CreateRfMatZero(rows, cols);
  
  std::vector<float> values(fcns.size());
  for(int row = 0; row < median->rows(); ++row) {
    for(int col = 0; col < median->cols(); ++col) {
      for(size_t target_idx = 0; target_idx < fcns.size(); ++target_idx) {
        values[target_idx] = (*(fcns[target_idx]->stat(0)))(row, col);
      }
      (*median)(row, col) = rv::stat::Median(values);
    }
  }
  
  TargetPtr target = boost::make_shared<Target>(median);
  return std::vector<TargetPtr>(1, target);
}

} //ns rf
} //ns rv
