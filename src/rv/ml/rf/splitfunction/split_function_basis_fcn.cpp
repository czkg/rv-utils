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

#include <rv/ml/rf/splitfunction/split_function_basis_fcn.h>

#include <rv/eigen/io/csv.h>

namespace rv {
namespace rf {

void SplitFunctionBasisFcn::SetUp(const SplitFunctionParameter& param, 
    const std::vector<SamplePtr>& samples) {

  //load basis fcns if needed
  basis_fcns_ = CreateRfMat(0, 0);

  std::string basis_csv = param.basis_csv();
  rv::eigen::ReadCsv(basis_csv, *basis_fcns_);

  LOG_INFO << "[SPLITFUNCTIONBASISFCN] using " << basis_fcns_->cols() << 
    " basis vectors of dimension " << basis_fcns_->rows();
}


boost::shared_ptr< SplitFunction > SplitFunctionBasisFcn::Generate() const {
  boost::shared_ptr<SplitFunctionBasisFcn> split_fcn = boost::make_shared<SplitFunctionBasisFcn>();
  
  int basis_fcn_idx = rv::rand::Rand<int>::Uniform(0, basis_fcns_->cols());
  
  split_fcn->basis_fcn_ = CreateRfMat(0, 0);
  (*(*split_fcn).basis_fcn_) = basis_fcns_->col(basis_fcn_idx);

  return split_fcn;
}

float SplitFunctionBasisFcn::Compute(SamplePtr sample) const {
  int dim = sample->dim();

  RfMat X(1, dim);
  int d = 0;
  for(int c = 0; c < sample->channels(); ++c) {
    for(int h = 0; h < sample->height(); ++h) {
      for(int w = 0; w < sample->width(); ++w) {
        X(0, d) = sample->at(c, h, w);
        d++;
      }
    }
  }

  if(X.cols() != basis_fcn_->rows()) {
    LOG_ERROR << "dimension of sample does not agree with dimension of basis fcn";
  }

  RfMat val = X * (*basis_fcn_);

  if(val.rows() == 1 && val.cols() == 1) {
    return val(0, 0);
  }
  else {
    LOG_ERROR << "invalid result val = \n " << X;
  }
}


} //ns rf
} //ns rv
