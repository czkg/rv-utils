#ifndef RV_CAMERA_CAMERA_IMAGE_HPP
#define RV_CAMERA_CAMERA_IMAGE_HPP

#include <boost/date_time.hpp>
#include <opencv2/core/core.hpp>

namespace rv {
namespace camera {
       

class CameraImage {
public:
  CameraImage() {}
  
  CameraImage(cv::Mat& im) : im_(im) {
    ts_ = boost::posix_time::microsec_clock::universal_time();
  }
  
  CameraImage(boost::posix_time::ptime& ts, cv::Mat& im) : ts_(ts), im_(im) { }
    
public:
  boost::posix_time::ptime ts_; 
  cv::Mat im_;
};

 

}
}


#endif
