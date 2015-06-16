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

#include <rv/ml/rf/leafnodefcn/classificationleafnodefcn.h>

namespace rv {
namespace rf {

boost::shared_ptr<LeafNodeFcn> ClassificationLeafNodeFcn::Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const std::vector<TargetPtr>& targets) const {
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMatPtr probs = CreateRfMatZero(rows, cols);
  
  double sum = 0;
  for(size_t tidx = 0; tidx < targets.size(); ++tidx) {
    RfMatPtr data = targets[tidx]->data();
    *probs = (*probs) + (*data);
    sum += data->sum();
  }
  *probs = (*probs) * (1.0 / sum);
  
  LeafNodeFcnPtr stat = boost::make_shared<ClassificationLeafNodeFcn>();
  stat->add_stat(probs);
  
  return stat;
}

std::vector<TargetPtr> ClassificationLeafNodeFcn::Eval(
    const SamplePtr sample,
    const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {
  int rows = fcns[0]->stat(0)->rows();
  int cols = fcns[0]->stat(0)->cols();
  RfMatPtr probs = CreateRfMatZero(rows, cols);
  
  for(size_t idx = 0; idx < fcns.size(); ++idx) {
    *probs = (*probs) + (*(fcns[idx]->stat(0)));
  }
  
  *probs = (*probs) * (1.0 / fcns.size());
  
  TargetPtr target = boost::make_shared<Target>(probs);
  return std::vector<TargetPtr>(1, target);
}


} //ns rf
} //ns rv
