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

#ifndef RF_SPLITFUNCTIONPIXELDIFFERENCEDEPENDENT_H
#define RF_SPLITFUNCTIONPIXELDIFFERENCEDEPENDENT_H

#include <fstream>

#include <opencv2/core/core.hpp>
#include <boost/make_shared.hpp>

#include <rv/ml/rf/splitfunction/splitfunction.h>

#include <rv/rand/rand.h>


namespace rv {
namespace rf {
    
class SplitFunctionPixelDifferenceDependent : public SplitFunction {
public:
  SplitFunctionPixelDifferenceDependent() {}
  virtual ~SplitFunctionPixelDifferenceDependent() {}
  
  virtual boost::shared_ptr<SplitFunction> Copy() const {
    boost::shared_ptr<SplitFunctionPixelDifferenceDependent> split_fcn = boost::make_shared<SplitFunctionPixelDifferenceDependent>();
    split_fcn->threshold_ = threshold_;
    split_fcn->slice_ = slice_;
    split_fcn->p1_ = p1_;
    split_fcn->p2_ = p2_;

    return split_fcn;
  }

  
  
  virtual boost::shared_ptr<SplitFunction> Generate() const;
  
  virtual float Compute(SamplePtr sample) const;
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    SplitFunction::Save(ar);

    ar << slice_;
    ar << p1_.x;
    ar << p1_.y;
    ar << p2_.x;
    ar << p2_.y;
  }

  virtual void Load(rv::io::SerializationIn& ar) {
    SplitFunction::Load(ar);

    ar >> slice_;
    ar >> p1_.x;
    ar >> p1_.y;
    ar >> p2_.x;
    ar >> p2_.y;
  }
  
  virtual SplitFunctionParameter::SplitFunctionType type() const { return SplitFunctionParameter::PIXEL_DIFFERENCE_DEPENDENT; }
    
private:
  int slice_;
  cv::Point p1_;
  cv::Point p2_;    

DISABLE_COPY_AND_ASSIGN(SplitFunctionPixelDifferenceDependent);
};

}
}

#endif
