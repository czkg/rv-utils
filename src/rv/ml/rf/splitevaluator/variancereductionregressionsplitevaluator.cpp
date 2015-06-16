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

#include <rv/ml/rf/splitevaluator/regressionsplitevaluator.h>

float rv::rf::VarianceReductionRegressionSplitEvaluator::Purity(
    const std::vector<TargetPtr>& targets) const {
  
  float var = 0;
  for(size_t target_idx_1 = 0; target_idx_1 < targets.size(); ++target_idx_1) {
    RfMatPtr t_1 = targets[target_idx_1]->data();
    
    for(size_t target_idx_2 = 0; target_idx_2 < targets.size(); ++target_idx_2) {
      RfMatPtr t_2 = targets[target_idx_2]->data();
      
      for(int row = 0; row < t_1->rows(); ++row) {
        for(int col = 0; col < t_1->cols(); ++col) {
          float diff = (*t_1)(row, col) - (*t_2)(row, col);
          var = var + diff * diff;
        }
      }
    }
  }
  
  return var;
}
