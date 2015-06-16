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

LeafNodeFcnPtr MeanStdRegressionLeafNodeFcn::Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const std::vector<TargetPtr>& targets) const {
  int rows = targets[0]->data()->rows();
  int cols = targets[0]->data()->cols();
  RfMatPtr mean = CreateRfMatZero(rows, cols);
  
  for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
    *mean = (*mean) + (*(targets[target_idx]->data()));
  }
  *mean = (*mean) * (1.0 / double(targets.size()));
 
  RfMatPtr var = CreateRfMatZero(rows, cols);
  if(targets.size() > 1) {
    for(size_t target_idx = 0; target_idx < targets.size(); ++target_idx) {
      RfMat val = (*(targets[target_idx]->data())) - (*mean);
      *var = (*var) + val.array().square().matrix();
    }
    *var = (*var) * (1.0 / float(targets.size() - 1));
  }
  else {
    std::cout << "[WARNING] number of targets = " << targets.size() 
      << " for variance computation - setting to -1" << std::endl;
    var->setConstant(-1);
  }
  
  LeafNodeFcnPtr stat = boost::make_shared<MeanStdRegressionLeafNodeFcn>();
  stat->add_stat(mean);
  stat->add_stat(var);
  
  return stat;
}
  
std::vector<TargetPtr> MeanStdRegressionLeafNodeFcn::Eval(
    const SamplePtr sample,
    const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {
  int rows = fcns[0]->stat(0)->rows();
  int cols = fcns[0]->stat(0)->cols();
  RfMatPtr mean = CreateRfMatZero(rows, cols);

  for(size_t i = 0; i < fcns.size(); ++i) {
    *mean = (*mean) + (*(fcns[i]->stat(0)));
  }
  *mean = (*mean) * (1.0 / float(fcns.size()));
  
 
  RfMatPtr var = CreateRfMatZero(rows, cols);
  for(size_t i = 0; i < fcns.size(); ++i) {
    *var = (*var) + (*(fcns[i]->stat(1)));
  }
  *var = (*var) * (1.0 / float(fcns.size()));
  
  TargetPtr target_mean = boost::make_shared<Target>(mean);
  TargetPtr target_var = boost::make_shared<Target>(var);
  
  std::vector<TargetPtr> target(2);
  target[0] = target_mean;
  target[1] = target_var;

  return target;
}


} //ns rf
} //ns rv
