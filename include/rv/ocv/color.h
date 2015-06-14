#ifndef RV_OCV_COLOR_H
#define RV_OCV_COLOR_H

#include <opencv2/core/core.hpp>

#include <rv/ocv/convert.h>


namespace rv {
namespace ocv {

  
inline std::vector<cv::Vec3f> hsv3f(size_t n) {
  float s = 1;
  float v = 1;

  std::vector<cv::Vec3f> colors(n);
  for(size_t i = 0; i < n; ++i) {
    float h = 360.0 * float(i) / float(n);
    colors[i] = hsv2Rgb(cv::Vec3f(h, s, v));
  }

  return colors;
}

inline std::vector<cv::Scalar> hsv(size_t n) {
  std::vector<cv::Vec3f> hsv_colors_3 = hsv3f(n);
  
  std::vector<cv::Scalar> hsv_colors(n);
  for(size_t idx = 0; idx < hsv_colors.size(); ++idx) {
    cv::Vec3f color = hsv_colors_3[idx] * 255;
    hsv_colors[idx] = cv::Scalar(color(0), color(1), color(2));
  }
  
  return hsv_colors;
}

  
} //ns cv
} //ns rv

#endif //OCV_COLOR_H
