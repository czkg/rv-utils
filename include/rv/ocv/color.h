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
