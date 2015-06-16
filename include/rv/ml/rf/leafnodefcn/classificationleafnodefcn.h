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

#ifndef RF_CLASSIFICATIONLEAFNODEFCN_H
#define RF_CLASSIFICATIONLEAFNODEFCN_H

#include <vector>
#include <iostream>

#include <boost/shared_ptr.hpp>

#include <opencv2/core/core.hpp>

#include <rv/ml/rf/leafnodefcn/leafnodefcn.h>

namespace rv {
namespace rf {
    
class ClassificationLeafNodeFcn : public LeafNodeFcn {        
public:
  ClassificationLeafNodeFcn() {}
  virtual ~ClassificationLeafNodeFcn() {}
  
  virtual boost::shared_ptr<LeafNodeFcn> Copy() const {
    boost::shared_ptr<ClassificationLeafNodeFcn> fcn = boost::make_shared<ClassificationLeafNodeFcn>();
    fcn->stat_.resize(stat_.size());
    for(size_t stat_idx = 0; stat_idx < stat_.size(); ++stat_idx) {
      fcn->stat_[stat_idx] = CopyRfMat(stat_[stat_idx]);
    }
    
    return fcn;
  }
  
  virtual boost::shared_ptr<LeafNodeFcn> Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const VecTargetPtr& targets) const;

  virtual VecTargetPtr Eval(const SamplePtr sample,
      const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const;

  
  virtual LeafNodeFcnParameter::LeafNodeFcnType type() const { return LeafNodeFcnParameter::CLASSIFICATION; }
  
DISABLE_COPY_AND_ASSIGN(ClassificationLeafNodeFcn);
};


}
}

#endif
