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
