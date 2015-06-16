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
#include <rv/log/log.h>

#include <math.h>


namespace rv {
namespace rf {

LeafNodeFcnPtr RegressionRegressionLeafNodeFcn::Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const std::vector<TargetPtr>& targets) const {
 
  float lambda = param.lambda();
  bool use_bias = param.use_bias();
  unsigned int param_poly_degree = param.poly_degree();
  bool weighted_regression = param.weighted_regression();

  int sample_dim = samples[0]->channels() * samples[0]->height() 
    * samples[0]->width();
  int N = param_poly_degree * sample_dim;
  int M = samples.size(); 
  int K = targets[0]->data()->rows() * targets[0]->data()->cols();
  
  if(use_bias) {
    N = N + 1;
  }
  
  if(N == 0) {
    LOG_ERROR << "if no bias is used, poly degree has to be at least 1";
  }

  //Create X and T matrix
  RfMat X(N, M);
  RfMat T(K, M);

  for(int m = 0; m < M; ++m) {
    SamplePtr sample = samples[m];
    RfMatPtr t = targets[m]->data();
    float t_w = targets[m]->weight();
    int n = 0;
    for(int c = 0; c < sample->channels(); ++c) {
      for(int h = 0; h < sample->height(); ++h) {
        for(int w = 0; w < sample->width(); ++w) {
          float sample_val = sample->at(c, h, w);
          float poly_val = sample_val;
          for(unsigned int pd = 0; pd < param_poly_degree; ++pd) {
            if(weighted_regression) {
              X(n, m) = t_w * poly_val;
            }
            else {
              X(n, m) = poly_val;
            }
            poly_val = poly_val * sample_val;
            n++;
          }
        }
      }
    }
    //add bias
    if(use_bias) {
      X(n, m) = 1;
      n++;
    }

    int k = 0;
    for(int r = 0; r < t->rows(); ++r) {
      for(int c = 0; c < t->cols(); ++c) {
        T(k, m) = (*t)(r, c);
        k++;
      }
    }
  }

  //Create Pseuo-Inverse
  RfMat Xt = X.transpose();
  RfMat XXt = X * Xt;
  if(lambda > 0) {
    XXt += ( lambda * RfMat::Identity(XXt.rows(), XXt.cols()) );
  }

  RfMat XXtinv = XXt.inverse();

  //Compute A
  RfMatPtr A = CreateRfMat(0, 0);
  *A = T * Xt * XXtinv;

  //check A matrix
  for(int row = 0; row < (*A).rows(); ++row) {
    for(int col = 0; col < (*A).cols(); ++col) {
      float val = (*A)(row, col);
      if(!std::isfinite(val)) {
        LOG_ERROR << "A matrix contains a invalid value: " << val << "\n\n"
          << "X = \n" << X << "\n\n"
          << "Xt = \n" << Xt << "\n\n"
          << "XXt = \n" << XXt << "\n\n"
          << "XXtinv = \n" << XXtinv << "\n\n"
          << "T = \n" << T << "\n\n"
          << "A = \n" << (*A) << "\n\n";
      }
    }
  }


  boost::shared_ptr<RegressionRegressionLeafNodeFcn> fcn = 
    boost::make_shared<RegressionRegressionLeafNodeFcn>();
  fcn->set_A(A);
  fcn->set_target_rows(targets[0]->data()->rows());
  fcn->set_target_cols(targets[0]->data()->cols());
  fcn->set_use_bias(use_bias);
  fcn->set_poly_degree(param_poly_degree);
  
  return fcn;
}
  


std::vector<TargetPtr> RegressionRegressionLeafNodeFcn::Eval(
    const SamplePtr sample,
    const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const {

  boost::shared_ptr<RegressionRegressionLeafNodeFcn> fcn = 
    boost::static_pointer_cast<RegressionRegressionLeafNodeFcn>(fcns[0]);
  int target_rows = fcn->target_rows();
  // int target_cols = fcn->target_cols();
  bool use_bias = fcn->use_bias();
  unsigned int poly_degree = fcn->poly_degree();

  //create sample matrix
  int N = poly_degree * sample->channels() * sample->height() * sample->width();
  if(use_bias) {
    N = N + 1;
  }

  if(N == 0) {
    LOG_ERROR << "if no bias is used, poly degree has to be at least 1";
  }

  RfMat X(N, 1);
  int n = 0;
  for(int c = 0; c < sample->channels(); ++c) {
    for(int h = 0; h < sample->height(); ++h) {
      for(int w = 0; w < sample->width(); ++w) {
        float sample_val = sample->at(c, h, w);
        float poly_val = sample_val;
        for(unsigned int pd = 0; pd < poly_degree; ++pd) {
          X(n, 0) = poly_val;
          poly_val = poly_val * sample_val;
          n++;
        }
      }
    }
  }
  if(use_bias) {
    X(n, 0) = 1;
    n++;
  }

  //accumulate regression matrices
  RfMat A = *(fcn->A());
  // std::cout << "---- Add A ----" << std::endl;
  for(size_t fcn_idx = 1; fcn_idx < fcns.size(); ++fcn_idx) {
    boost::shared_ptr<RegressionRegressionLeafNodeFcn> fcn = 
      boost::static_pointer_cast<RegressionRegressionLeafNodeFcn>(fcns[fcn_idx]);

    RfMatPtr Aadd = fcn->A();
    // std::cout << Aadd->rows() << "/" << Aadd->cols() << std::endl;
    A = A + (*Aadd);
  }
  // std::cout << "---- ---- ----" << std::endl;
  A = (1.0 / float(fcns.size())) * A;

  RfMatPtr t = CreateRfMat(0, 0);
  *t = A * X;

  TargetPtr target = boost::make_shared<Target>(t); //TODO: how to reshape?
  return std::vector<TargetPtr>(1, target);
}



} //ns rf
} //ns rv
