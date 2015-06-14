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
