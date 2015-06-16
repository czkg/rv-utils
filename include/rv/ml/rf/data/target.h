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

#ifndef RF_TARGET_H
#define RF_TARGET_H

#include <fstream>

#include <boost/shared_ptr.hpp>

#include <opencv2/core/core.hpp>

#include <rv/ml/rf/common.h>

namespace rv {
namespace rf {
    
class Target {    
public:
  Target(RfMatPtr data) : data_(data), weight_(1.0) {}
  Target(RfMatPtr data, float weight) : data_(data), weight_(weight) {}
  
  Target(int label, int max_label) {
    data_ = CreateRfMatZero(1, max_label);
    (*data_)(0, label) = 1.0;
    weight_ = 1.0;
  }
  
  Target(int label, int max_label, float weight) {
    data_ = CreateRfMatZero(1, max_label);
    (*data_)(0, label) = weight;
    weight_ = weight;
  }
  
  virtual ~Target() {}
  
  RfMatPtr data() const { return data_; }
  float weight() const { return weight_; }
  
private:
  RfMatPtr data_;
  float weight_;

};

typedef boost::shared_ptr<Target> TargetPtr;
typedef std::vector<TargetPtr> VecTargetPtr;
typedef boost::shared_ptr<VecTargetPtr> VecPtrTargetPtr;

}
}


#endif
