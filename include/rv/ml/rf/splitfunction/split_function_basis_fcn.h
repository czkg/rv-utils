#ifndef RV_ML_RF_SPLIT_FUNCTION_BASIS_FCN_H
#define RV_ML_RF_SPLIT_FUNCTION_BASIS_FCN_H

#include <fstream>

#include <opencv2/core/core.hpp>
#include <boost/make_shared.hpp>

#include <rv/ml/rf/splitfunction/splitfunction.h>
#include <rv/ml/rf/common.h>

#include <rv/rand/rand.h>


namespace rv {
namespace rf {
    
class SplitFunctionBasisFcn : public SplitFunction {
public:
  SplitFunctionBasisFcn() {}
  virtual ~SplitFunctionBasisFcn() {}
  
  virtual boost::shared_ptr<SplitFunction> Copy() const {
    boost::shared_ptr<SplitFunctionBasisFcn> split_fcn = boost::make_shared<SplitFunctionBasisFcn>();
    split_fcn->threshold_ = threshold_;
    split_fcn->basis_fcn_ = CopyRfMat(basis_fcn_);

    return split_fcn;
  }

  virtual void SetUp(const SplitFunctionParameter& param, 
    const std::vector<SamplePtr>& samples);
  virtual boost::shared_ptr<SplitFunction> Generate() const;
  
  virtual float Compute(SamplePtr sample) const;
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    SplitFunction::Save(ar);
    
    int rows = basis_fcn_->rows();
    int cols = basis_fcn_->cols();
    ar << rows;
    ar << cols;
    for(int row = 0; row < basis_fcn_->rows(); ++row) {
      for(int col = 0; col < basis_fcn_->cols(); ++col) {
        float val = (*basis_fcn_)(row, col);
        ar << val;
      }
    }
  }
  
  virtual void Load(rv::io::SerializationIn& ar) {
    SplitFunction::Load(ar);

    int row, col;
    ar >> row;
    ar >> col;

    basis_fcn_ = CreateRfMat(row, col);
    for(int row = 0; row < basis_fcn_->rows(); ++row) {
      for(int col = 0; col < basis_fcn_->cols(); ++col) {
        float val;
        ar >> val;

        (*basis_fcn_)(row, col) = val;
      }
    }

  }
  
  virtual SplitFunctionParameter::SplitFunctionType type() const { return SplitFunctionParameter::BASIS_FCN; }
    
private:
  RfMatPtr basis_fcn_;

  //gen
  RfMatPtr basis_fcns_;

DISABLE_COPY_AND_ASSIGN(SplitFunctionBasisFcn);
};

} //ns rf
} //ns rv

#endif //RV_ML_RF_SPLIT_FUNCTION_BASIS_FCN_H
