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

#include <rv/ml/rf/splitfunction/splitfunctionpixeldifference.h>

namespace rv {
namespace rf {

boost::shared_ptr< SplitFunction > SplitFunctionPixelDifference::Generate() const {
  boost::shared_ptr<SplitFunctionPixelDifference> split_fcn = boost::make_shared<SplitFunctionPixelDifference>();
  
  split_fcn->slice_ = rv::rand::Rand<int>::Uniform(0, gen_n_slices_);
  
  split_fcn->p1_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
  split_fcn->p1_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  if(gen_fix_one_) {
    split_fcn->p2_.x = gen_x_[gen_x_.size() / 2];
    split_fcn->p2_.y = gen_y_[gen_y_.size() / 2];
  }
  else {
    split_fcn->p2_.x = gen_x_[rv::rand::Rand<int>::Uniform(0, gen_x_.size())];
    split_fcn->p2_.y = gen_y_[rv::rand::Rand<int>::Uniform(0, gen_y_.size())];
  }
  
  return split_fcn;
}

float SplitFunctionPixelDifference::Compute(SamplePtr sample) const {
  return (*sample)(slice_, p1_.y, p1_.x) - (*sample)(slice_, p2_.y, p2_.x);
}


} //ns rf
} //ns rv
