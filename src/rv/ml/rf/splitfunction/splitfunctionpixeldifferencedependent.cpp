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

#include <rv/ml/rf/splitfunction/splitfunctionpixeldifferencedependent.h>

namespace rv {
namespace rf {

boost::shared_ptr< rv::rf::SplitFunction > rv::rf::SplitFunctionPixelDifferenceDependent::Generate() const {
  boost::shared_ptr<SplitFunctionPixelDifferenceDependent> split_fcn = boost::make_shared<SplitFunctionPixelDifferenceDependent>();
  
  split_fcn->slice_ = rv::rand::Rand<int>::Uniform(0, gen_n_slices_);
  
  split_fcn->p1_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
  split_fcn->p1_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  if(gen_fix_one_) {
    split_fcn->p2_.x = 0;
    split_fcn->p2_.y = 0;
  }
  else {
    split_fcn->p2_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
    split_fcn->p2_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  }
  
  return split_fcn;
}

float rv::rf::SplitFunctionPixelDifferenceDependent::Compute(rv::rf::SamplePtr sample) const {
  float dependent = (*sample)(slice_, 0, 0);

  int x1 = p1_.x / dependent;
  int x2 = p2_.x / dependent;
  int y1 = p1_.y / dependent;
  int y2 = p2_.y / dependent;

  // std::cout << "diff " << x1 << "/" << y1 << ", " << x2 << "/" << y2 << std::endl;

  float val1 = (*sample)(slice_, y1, x1);
  float val2 = (*sample)(slice_, y2, x2);
  return val1 - val2;
}


} //ns rf
} //ns rv
