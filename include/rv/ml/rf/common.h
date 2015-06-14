#ifndef RV_ML_RF_COMMON
#define RV_ML_RF_COMMON

#include <Eigen/Dense>

#include <boost/make_shared.hpp>



#define DISABLE_COPY_AND_ASSIGN(classname) \
private:\
  classname(const classname&);\
  classname& operator=(const classname&)




namespace rv {
namespace rf {

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RfMat;
// typedef Eigen::Block<float> RfMatBlock;

typedef boost::shared_ptr<RfMat> RfMatPtr ;

RfMatPtr CreateRfMat(int rows, int cols);
RfMatPtr CreateRfMatZero(int rows, int cols);
RfMatPtr CopyRfMat(const RfMatPtr& mat);

} //ns rf 
} //ns rv

#endif //RV_ML_RF_COMMON
