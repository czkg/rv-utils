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

#include <rv/ml/rf/splitfunction/make_split_function.h>

#include <rv/ml/rf/splitfunction/splitfunctionpixeldifference.h>
#include <rv/ml/rf/splitfunction/splitfunctionpixeldifferencedependent.h>
#include <rv/ml/rf/splitfunction/splitfunctionpixelvalue.h>
#include <rv/ml/rf/splitfunction/split_function_basis_fcn.h>


rv::rf::SplitFunctionPtr rv::rf::MakeSplitFunction(rv::rf::SplitFunctionParameter::SplitFunctionType type) {
  if(type == SplitFunctionParameter::PIXEL_VALUE) {
    return boost::make_shared<SplitFunctionPixelValue>();
  }
  else if(type == SplitFunctionParameter::PIXEL_DIFFERENCE) {
    return boost::make_shared<SplitFunctionPixelDifference>();
  }
  else if(type == SplitFunctionParameter::PIXEL_DIFFERENCE_DEPENDENT) {
    return boost::make_shared<SplitFunctionPixelDifferenceDependent>();
  }
  else if(type == SplitFunctionParameter::BASIS_FCN) {
    return boost::make_shared<SplitFunctionBasisFcn>();
  }
  else {
    LOG_ERROR << "unknown split function type: " << type;
  }
}
