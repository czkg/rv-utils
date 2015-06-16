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

#ifndef RV_OCV_COLORMAP_JET_H
#define RV_OCV_COLORMAP_JET_H

#include "colormap.h"

namespace rv {
namespace ocv {

template <typename Dtype>
class ColorMapJet : public ColorMap<Dtype> {
public:
  static ColorMapJet<Dtype>& i() {
    static ColorMapJet<Dtype> instance;
    return instance;
  }
  
  virtual std::string name() const {
    return "jet";
  }
  
protected:
  ColorMapJet() {
    //init colors 
    this->map_.push_back(cv::Vec3b(127, 0, 0));
    this->map_.push_back(cv::Vec3b(132, 0, 0));
    this->map_.push_back(cv::Vec3b(136, 0, 0));
    this->map_.push_back(cv::Vec3b(141, 0, 0));
    this->map_.push_back(cv::Vec3b(145, 0, 0));
    this->map_.push_back(cv::Vec3b(150, 0, 0));
    this->map_.push_back(cv::Vec3b(154, 0, 0));
    this->map_.push_back(cv::Vec3b(159, 0, 0));
    this->map_.push_back(cv::Vec3b(163, 0, 0));
    this->map_.push_back(cv::Vec3b(168, 0, 0));
    this->map_.push_back(cv::Vec3b(172, 0, 0));
    this->map_.push_back(cv::Vec3b(177, 0, 0));
    this->map_.push_back(cv::Vec3b(182, 0, 0));
    this->map_.push_back(cv::Vec3b(186, 0, 0));
    this->map_.push_back(cv::Vec3b(191, 0, 0));
    this->map_.push_back(cv::Vec3b(195, 0, 0));
    this->map_.push_back(cv::Vec3b(200, 0, 0));
    this->map_.push_back(cv::Vec3b(204, 0, 0));
    this->map_.push_back(cv::Vec3b(209, 0, 0));
    this->map_.push_back(cv::Vec3b(213, 0, 0));
    this->map_.push_back(cv::Vec3b(218, 0, 0));
    this->map_.push_back(cv::Vec3b(222, 0, 0));
    this->map_.push_back(cv::Vec3b(227, 0, 0));
    this->map_.push_back(cv::Vec3b(232, 0, 0));
    this->map_.push_back(cv::Vec3b(236, 0, 0));
    this->map_.push_back(cv::Vec3b(241, 0, 0));
    this->map_.push_back(cv::Vec3b(245, 0, 0));
    this->map_.push_back(cv::Vec3b(250, 0, 0));
    this->map_.push_back(cv::Vec3b(254, 0, 0));
    this->map_.push_back(cv::Vec3b(255, 0, 0));
    this->map_.push_back(cv::Vec3b(255, 0, 0));
    this->map_.push_back(cv::Vec3b(255, 0, 0));
    this->map_.push_back(cv::Vec3b(255, 0, 0));
    this->map_.push_back(cv::Vec3b(255, 4, 0));
    this->map_.push_back(cv::Vec3b(255, 8, 0));
    this->map_.push_back(cv::Vec3b(255, 12, 0));
    this->map_.push_back(cv::Vec3b(255, 16, 0));
    this->map_.push_back(cv::Vec3b(255, 20, 0));
    this->map_.push_back(cv::Vec3b(255, 24, 0));
    this->map_.push_back(cv::Vec3b(255, 28, 0));
    this->map_.push_back(cv::Vec3b(255, 32, 0));
    this->map_.push_back(cv::Vec3b(255, 36, 0));
    this->map_.push_back(cv::Vec3b(255, 40, 0));
    this->map_.push_back(cv::Vec3b(255, 44, 0));
    this->map_.push_back(cv::Vec3b(255, 48, 0));
    this->map_.push_back(cv::Vec3b(255, 52, 0));
    this->map_.push_back(cv::Vec3b(255, 56, 0));
    this->map_.push_back(cv::Vec3b(255, 60, 0));
    this->map_.push_back(cv::Vec3b(255, 64, 0));
    this->map_.push_back(cv::Vec3b(255, 68, 0));
    this->map_.push_back(cv::Vec3b(255, 72, 0));
    this->map_.push_back(cv::Vec3b(255, 76, 0));
    this->map_.push_back(cv::Vec3b(255, 80, 0));
    this->map_.push_back(cv::Vec3b(255, 84, 0));
    this->map_.push_back(cv::Vec3b(255, 88, 0));
    this->map_.push_back(cv::Vec3b(255, 92, 0));
    this->map_.push_back(cv::Vec3b(255, 96, 0));
    this->map_.push_back(cv::Vec3b(255, 100, 0));
    this->map_.push_back(cv::Vec3b(255, 104, 0));
    this->map_.push_back(cv::Vec3b(255, 108, 0));
    this->map_.push_back(cv::Vec3b(255, 112, 0));
    this->map_.push_back(cv::Vec3b(255, 116, 0));
    this->map_.push_back(cv::Vec3b(255, 120, 0));
    this->map_.push_back(cv::Vec3b(255, 124, 0));
    this->map_.push_back(cv::Vec3b(255, 128, 0));
    this->map_.push_back(cv::Vec3b(255, 132, 0));
    this->map_.push_back(cv::Vec3b(255, 136, 0));
    this->map_.push_back(cv::Vec3b(255, 140, 0));
    this->map_.push_back(cv::Vec3b(255, 144, 0));
    this->map_.push_back(cv::Vec3b(255, 148, 0));
    this->map_.push_back(cv::Vec3b(255, 152, 0));
    this->map_.push_back(cv::Vec3b(255, 156, 0));
    this->map_.push_back(cv::Vec3b(255, 160, 0));
    this->map_.push_back(cv::Vec3b(255, 164, 0));
    this->map_.push_back(cv::Vec3b(255, 168, 0));
    this->map_.push_back(cv::Vec3b(255, 172, 0));
    this->map_.push_back(cv::Vec3b(255, 176, 0));
    this->map_.push_back(cv::Vec3b(255, 180, 0));
    this->map_.push_back(cv::Vec3b(255, 184, 0));
    this->map_.push_back(cv::Vec3b(255, 188, 0));
    this->map_.push_back(cv::Vec3b(255, 192, 0));
    this->map_.push_back(cv::Vec3b(255, 196, 0));
    this->map_.push_back(cv::Vec3b(255, 200, 0));
    this->map_.push_back(cv::Vec3b(255, 204, 0));
    this->map_.push_back(cv::Vec3b(255, 208, 0));
    this->map_.push_back(cv::Vec3b(255, 212, 0));
    this->map_.push_back(cv::Vec3b(255, 216, 0));
    this->map_.push_back(cv::Vec3b(254, 220, 0));
    this->map_.push_back(cv::Vec3b(250, 224, 0));
    this->map_.push_back(cv::Vec3b(247, 228, 0));
    this->map_.push_back(cv::Vec3b(244, 232, 2));
    this->map_.push_back(cv::Vec3b(241, 236, 5));
    this->map_.push_back(cv::Vec3b(237, 240, 8));
    this->map_.push_back(cv::Vec3b(234, 244, 12));
    this->map_.push_back(cv::Vec3b(231, 248, 15));
    this->map_.push_back(cv::Vec3b(228, 252, 18));
    this->map_.push_back(cv::Vec3b(225, 255, 21));
    this->map_.push_back(cv::Vec3b(221, 255, 24));
    this->map_.push_back(cv::Vec3b(218, 255, 28));
    this->map_.push_back(cv::Vec3b(215, 255, 31));
    this->map_.push_back(cv::Vec3b(212, 255, 34));
    this->map_.push_back(cv::Vec3b(208, 255, 37));
    this->map_.push_back(cv::Vec3b(205, 255, 41));
    this->map_.push_back(cv::Vec3b(202, 255, 44));
    this->map_.push_back(cv::Vec3b(199, 255, 47));
    this->map_.push_back(cv::Vec3b(195, 255, 50));
    this->map_.push_back(cv::Vec3b(192, 255, 54));
    this->map_.push_back(cv::Vec3b(189, 255, 57));
    this->map_.push_back(cv::Vec3b(186, 255, 60));
    this->map_.push_back(cv::Vec3b(183, 255, 63));
    this->map_.push_back(cv::Vec3b(179, 255, 66));
    this->map_.push_back(cv::Vec3b(176, 255, 70));
    this->map_.push_back(cv::Vec3b(173, 255, 73));
    this->map_.push_back(cv::Vec3b(170, 255, 76));
    this->map_.push_back(cv::Vec3b(166, 255, 79));
    this->map_.push_back(cv::Vec3b(163, 255, 83));
    this->map_.push_back(cv::Vec3b(160, 255, 86));
    this->map_.push_back(cv::Vec3b(157, 255, 89));
    this->map_.push_back(cv::Vec3b(154, 255, 92));
    this->map_.push_back(cv::Vec3b(150, 255, 95));
    this->map_.push_back(cv::Vec3b(147, 255, 99));
    this->map_.push_back(cv::Vec3b(144, 255, 102));
    this->map_.push_back(cv::Vec3b(141, 255, 105));
    this->map_.push_back(cv::Vec3b(137, 255, 108));
    this->map_.push_back(cv::Vec3b(134, 255, 112));
    this->map_.push_back(cv::Vec3b(131, 255, 115));
    this->map_.push_back(cv::Vec3b(128, 255, 118));
    this->map_.push_back(cv::Vec3b(125, 255, 121));
    this->map_.push_back(cv::Vec3b(121, 255, 124));
    this->map_.push_back(cv::Vec3b(118, 255, 128));
    this->map_.push_back(cv::Vec3b(115, 255, 131));
    this->map_.push_back(cv::Vec3b(112, 255, 134));
    this->map_.push_back(cv::Vec3b(108, 255, 137));
    this->map_.push_back(cv::Vec3b(105, 255, 141));
    this->map_.push_back(cv::Vec3b(102, 255, 144));
    this->map_.push_back(cv::Vec3b(99, 255, 147));
    this->map_.push_back(cv::Vec3b(95, 255, 150));
    this->map_.push_back(cv::Vec3b(92, 255, 154));
    this->map_.push_back(cv::Vec3b(89, 255, 157));
    this->map_.push_back(cv::Vec3b(86, 255, 160));
    this->map_.push_back(cv::Vec3b(83, 255, 163));
    this->map_.push_back(cv::Vec3b(79, 255, 166));
    this->map_.push_back(cv::Vec3b(76, 255, 170));
    this->map_.push_back(cv::Vec3b(73, 255, 173));
    this->map_.push_back(cv::Vec3b(70, 255, 176));
    this->map_.push_back(cv::Vec3b(66, 255, 179));
    this->map_.push_back(cv::Vec3b(63, 255, 183));
    this->map_.push_back(cv::Vec3b(60, 255, 186));
    this->map_.push_back(cv::Vec3b(57, 255, 189));
    this->map_.push_back(cv::Vec3b(54, 255, 192));
    this->map_.push_back(cv::Vec3b(50, 255, 195));
    this->map_.push_back(cv::Vec3b(47, 255, 199));
    this->map_.push_back(cv::Vec3b(44, 255, 202));
    this->map_.push_back(cv::Vec3b(41, 255, 205));
    this->map_.push_back(cv::Vec3b(37, 255, 208));
    this->map_.push_back(cv::Vec3b(34, 255, 212));
    this->map_.push_back(cv::Vec3b(31, 255, 215));
    this->map_.push_back(cv::Vec3b(28, 255, 218));
    this->map_.push_back(cv::Vec3b(24, 255, 221));
    this->map_.push_back(cv::Vec3b(21, 255, 224));
    this->map_.push_back(cv::Vec3b(18, 255, 228));
    this->map_.push_back(cv::Vec3b(15, 255, 231));
    this->map_.push_back(cv::Vec3b(12, 255, 234));
    this->map_.push_back(cv::Vec3b(8, 255, 237));
    this->map_.push_back(cv::Vec3b(5, 252, 241));
    this->map_.push_back(cv::Vec3b(2, 248, 244));
    this->map_.push_back(cv::Vec3b(0, 244, 247));
    this->map_.push_back(cv::Vec3b(0, 240, 250));
    this->map_.push_back(cv::Vec3b(0, 237, 254));
    this->map_.push_back(cv::Vec3b(0, 233, 255));
    this->map_.push_back(cv::Vec3b(0, 229, 255));
    this->map_.push_back(cv::Vec3b(0, 226, 255));
    this->map_.push_back(cv::Vec3b(0, 222, 255));
    this->map_.push_back(cv::Vec3b(0, 218, 255));
    this->map_.push_back(cv::Vec3b(0, 215, 255));
    this->map_.push_back(cv::Vec3b(0, 211, 255));
    this->map_.push_back(cv::Vec3b(0, 207, 255));
    this->map_.push_back(cv::Vec3b(0, 203, 255));
    this->map_.push_back(cv::Vec3b(0, 200, 255));
    this->map_.push_back(cv::Vec3b(0, 196, 255));
    this->map_.push_back(cv::Vec3b(0, 192, 255));
    this->map_.push_back(cv::Vec3b(0, 189, 255));
    this->map_.push_back(cv::Vec3b(0, 185, 255));
    this->map_.push_back(cv::Vec3b(0, 181, 255));
    this->map_.push_back(cv::Vec3b(0, 177, 255));
    this->map_.push_back(cv::Vec3b(0, 174, 255));
    this->map_.push_back(cv::Vec3b(0, 170, 255));
    this->map_.push_back(cv::Vec3b(0, 166, 255));
    this->map_.push_back(cv::Vec3b(0, 163, 255));
    this->map_.push_back(cv::Vec3b(0, 159, 255));
    this->map_.push_back(cv::Vec3b(0, 155, 255));
    this->map_.push_back(cv::Vec3b(0, 152, 255));
    this->map_.push_back(cv::Vec3b(0, 148, 255));
    this->map_.push_back(cv::Vec3b(0, 144, 255));
    this->map_.push_back(cv::Vec3b(0, 140, 255));
    this->map_.push_back(cv::Vec3b(0, 137, 255));
    this->map_.push_back(cv::Vec3b(0, 133, 255));
    this->map_.push_back(cv::Vec3b(0, 129, 255));
    this->map_.push_back(cv::Vec3b(0, 126, 255));
    this->map_.push_back(cv::Vec3b(0, 122, 255));
    this->map_.push_back(cv::Vec3b(0, 118, 255));
    this->map_.push_back(cv::Vec3b(0, 115, 255));
    this->map_.push_back(cv::Vec3b(0, 111, 255));
    this->map_.push_back(cv::Vec3b(0, 107, 255));
    this->map_.push_back(cv::Vec3b(0, 103, 255));
    this->map_.push_back(cv::Vec3b(0, 100, 255));
    this->map_.push_back(cv::Vec3b(0, 96, 255));
    this->map_.push_back(cv::Vec3b(0, 92, 255));
    this->map_.push_back(cv::Vec3b(0, 89, 255));
    this->map_.push_back(cv::Vec3b(0, 85, 255));
    this->map_.push_back(cv::Vec3b(0, 81, 255));
    this->map_.push_back(cv::Vec3b(0, 77, 255));
    this->map_.push_back(cv::Vec3b(0, 74, 255));
    this->map_.push_back(cv::Vec3b(0, 70, 255));
    this->map_.push_back(cv::Vec3b(0, 66, 255));
    this->map_.push_back(cv::Vec3b(0, 63, 255));
    this->map_.push_back(cv::Vec3b(0, 59, 255));
    this->map_.push_back(cv::Vec3b(0, 55, 255));
    this->map_.push_back(cv::Vec3b(0, 52, 255));
    this->map_.push_back(cv::Vec3b(0, 48, 255));
    this->map_.push_back(cv::Vec3b(0, 44, 255));
    this->map_.push_back(cv::Vec3b(0, 40, 255));
    this->map_.push_back(cv::Vec3b(0, 37, 255));
    this->map_.push_back(cv::Vec3b(0, 33, 255));
    this->map_.push_back(cv::Vec3b(0, 29, 255));
    this->map_.push_back(cv::Vec3b(0, 26, 255));
    this->map_.push_back(cv::Vec3b(0, 22, 255));
    this->map_.push_back(cv::Vec3b(0, 18, 254));
    this->map_.push_back(cv::Vec3b(0, 15, 250));
    this->map_.push_back(cv::Vec3b(0, 11, 245));
    this->map_.push_back(cv::Vec3b(0, 7, 241));
    this->map_.push_back(cv::Vec3b(0, 3, 236));
    this->map_.push_back(cv::Vec3b(0, 0, 232));
    this->map_.push_back(cv::Vec3b(0, 0, 227));
    this->map_.push_back(cv::Vec3b(0, 0, 222));
    this->map_.push_back(cv::Vec3b(0, 0, 218));
    this->map_.push_back(cv::Vec3b(0, 0, 213));
    this->map_.push_back(cv::Vec3b(0, 0, 209));
    this->map_.push_back(cv::Vec3b(0, 0, 204));
    this->map_.push_back(cv::Vec3b(0, 0, 200));
    this->map_.push_back(cv::Vec3b(0, 0, 195));
    this->map_.push_back(cv::Vec3b(0, 0, 191));
    this->map_.push_back(cv::Vec3b(0, 0, 186));
    this->map_.push_back(cv::Vec3b(0, 0, 182));
    this->map_.push_back(cv::Vec3b(0, 0, 177));
    this->map_.push_back(cv::Vec3b(0, 0, 172));
    this->map_.push_back(cv::Vec3b(0, 0, 168));
    this->map_.push_back(cv::Vec3b(0, 0, 163));
    this->map_.push_back(cv::Vec3b(0, 0, 159));
    this->map_.push_back(cv::Vec3b(0, 0, 154));
    this->map_.push_back(cv::Vec3b(0, 0, 150));
    this->map_.push_back(cv::Vec3b(0, 0, 145));
    this->map_.push_back(cv::Vec3b(0, 0, 141));
    this->map_.push_back(cv::Vec3b(0, 0, 136));
    this->map_.push_back(cv::Vec3b(0, 0, 132));
    this->map_.push_back(cv::Vec3b(0, 0, 127));
  }
  
private:
  ColorMapJet(const ColorMapJet<Dtype>& m);
  void operator=(const ColorMapJet<Dtype>& m);
};


} //ns cv
} //ns rv

#endif
