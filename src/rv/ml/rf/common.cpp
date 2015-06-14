#include <rv/ml/rf/common.h>

namespace rv {
namespace rf {

RfMatPtr CreateRfMat(int rows, int cols) {
  return boost::make_shared<RfMat>(rows, cols);
}

RfMatPtr CreateRfMatZero(int rows, int cols) {
  RfMatPtr mat = CreateRfMat(rows, cols);
  mat->setZero();
  return mat;
}

RfMatPtr CopyRfMat(const RfMatPtr& mat) {
  RfMatPtr new_mat = CreateRfMat(mat->rows(), mat->cols());
  *new_mat = *mat;
  return new_mat;
}


} //ns rf 
} //ns rv 
