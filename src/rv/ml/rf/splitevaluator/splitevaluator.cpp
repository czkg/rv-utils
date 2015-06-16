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

#include <rv/ml/rf/splitevaluator/splitevaluator.h>
#include <iostream>

float rv::rf::SplitEvaluator::Eval(const std::vector<TargetPtr>& lefttargets, 
    const std::vector<TargetPtr>& righttargets) const {
  
  float purity_left = Purity(lefttargets);
  float purity_right = Purity(righttargets);
  
  float normalize_left = 1.0;
  float normalize_right = 1.0;
  
  if(normalize_) {
    unsigned int n_left = lefttargets.size();
    unsigned int n_right = righttargets.size();
    unsigned int n_total = n_left + n_right;
    
    normalize_left = float(n_left) / float(n_total);
    normalize_right = float(n_right) / float(n_total);
  }
  
  float purity =  purity_left * normalize_left + purity_right * normalize_right;
  float weighted_purity = weight_ * purity;

  // std::cout << purity_left << ", " << purity_right << ", " 
  //   << normalize_left << ", " << normalize_right << ", " 
  //   << purity_left * normalize_left << ", " << purity_right * normalize_right;

  return weighted_purity;
}
