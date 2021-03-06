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

#ifndef RV_OCV_COLORMAP_COOL_WARM_H
#define RV_OCV_COLORMAP_COOL_WARM_H

#include "colormap.h"

namespace rv {
namespace ocv {

template <typename Dtype>
class ColorMapCoolWarm : public ColorMap<Dtype> {
public:
  static ColorMapCoolWarm<Dtype>& i() {
    static ColorMapCoolWarm<Dtype> instance;
    return instance;
  }
  
  virtual std::string name() const {
    return "cool_warm";
  }
  
protected:
  ColorMapCoolWarm() {
    //init colors 
    this->map_.push_back(cv::Vec3b(192, 76, 58));
    this->map_.push_back(cv::Vec3b(193, 77, 59));
    this->map_.push_back(cv::Vec3b(195, 79, 60));
    this->map_.push_back(cv::Vec3b(196, 81, 62));
    this->map_.push_back(cv::Vec3b(198, 83, 63));
    this->map_.push_back(cv::Vec3b(199, 84, 64));
    this->map_.push_back(cv::Vec3b(201, 86, 65));
    this->map_.push_back(cv::Vec3b(202, 88, 66));
    this->map_.push_back(cv::Vec3b(204, 90, 67));
    this->map_.push_back(cv::Vec3b(205, 91, 69));
    this->map_.push_back(cv::Vec3b(207, 93, 70));
    this->map_.push_back(cv::Vec3b(208, 95, 71));
    this->map_.push_back(cv::Vec3b(209, 96, 72));
    this->map_.push_back(cv::Vec3b(211, 98, 73));
    this->map_.push_back(cv::Vec3b(212, 100, 75));
    this->map_.push_back(cv::Vec3b(214, 102, 76));
    this->map_.push_back(cv::Vec3b(215, 103, 77));
    this->map_.push_back(cv::Vec3b(216, 105, 78));
    this->map_.push_back(cv::Vec3b(218, 107, 80));
    this->map_.push_back(cv::Vec3b(219, 108, 81));
    this->map_.push_back(cv::Vec3b(220, 110, 82));
    this->map_.push_back(cv::Vec3b(221, 112, 83));
    this->map_.push_back(cv::Vec3b(222, 113, 85));
    this->map_.push_back(cv::Vec3b(224, 115, 86));
    this->map_.push_back(cv::Vec3b(225, 117, 87));
    this->map_.push_back(cv::Vec3b(226, 118, 88));
    this->map_.push_back(cv::Vec3b(227, 120, 90));
    this->map_.push_back(cv::Vec3b(228, 121, 91));
    this->map_.push_back(cv::Vec3b(229, 123, 92));
    this->map_.push_back(cv::Vec3b(230, 125, 93));
    this->map_.push_back(cv::Vec3b(231, 126, 95));
    this->map_.push_back(cv::Vec3b(232, 128, 96));
    this->map_.push_back(cv::Vec3b(234, 130, 97));
    this->map_.push_back(cv::Vec3b(234, 131, 99));
    this->map_.push_back(cv::Vec3b(235, 133, 100));
    this->map_.push_back(cv::Vec3b(236, 134, 101));
    this->map_.push_back(cv::Vec3b(237, 136, 103));
    this->map_.push_back(cv::Vec3b(238, 137, 104));
    this->map_.push_back(cv::Vec3b(239, 139, 105));
    this->map_.push_back(cv::Vec3b(240, 141, 107));
    this->map_.push_back(cv::Vec3b(241, 142, 108));
    this->map_.push_back(cv::Vec3b(241, 144, 109));
    this->map_.push_back(cv::Vec3b(242, 145, 111));
    this->map_.push_back(cv::Vec3b(243, 147, 112));
    this->map_.push_back(cv::Vec3b(244, 148, 113));
    this->map_.push_back(cv::Vec3b(244, 149, 115));
    this->map_.push_back(cv::Vec3b(245, 151, 116));
    this->map_.push_back(cv::Vec3b(246, 152, 117));
    this->map_.push_back(cv::Vec3b(246, 154, 119));
    this->map_.push_back(cv::Vec3b(247, 155, 120));
    this->map_.push_back(cv::Vec3b(248, 157, 122));
    this->map_.push_back(cv::Vec3b(248, 158, 123));
    this->map_.push_back(cv::Vec3b(249, 160, 124));
    this->map_.push_back(cv::Vec3b(249, 161, 126));
    this->map_.push_back(cv::Vec3b(250, 162, 127));
    this->map_.push_back(cv::Vec3b(250, 164, 128));
    this->map_.push_back(cv::Vec3b(251, 165, 130));
    this->map_.push_back(cv::Vec3b(251, 166, 131));
    this->map_.push_back(cv::Vec3b(251, 168, 133));
    this->map_.push_back(cv::Vec3b(252, 169, 134));
    this->map_.push_back(cv::Vec3b(252, 170, 135));
    this->map_.push_back(cv::Vec3b(252, 172, 137));
    this->map_.push_back(cv::Vec3b(253, 173, 138));
    this->map_.push_back(cv::Vec3b(253, 174, 139));
    this->map_.push_back(cv::Vec3b(253, 175, 141));
    this->map_.push_back(cv::Vec3b(253, 177, 142));
    this->map_.push_back(cv::Vec3b(254, 178, 144));
    this->map_.push_back(cv::Vec3b(254, 179, 145));
    this->map_.push_back(cv::Vec3b(254, 180, 146));
    this->map_.push_back(cv::Vec3b(254, 181, 148));
    this->map_.push_back(cv::Vec3b(254, 183, 149));
    this->map_.push_back(cv::Vec3b(254, 184, 151));
    this->map_.push_back(cv::Vec3b(254, 185, 152));
    this->map_.push_back(cv::Vec3b(254, 186, 153));
    this->map_.push_back(cv::Vec3b(254, 187, 155));
    this->map_.push_back(cv::Vec3b(254, 188, 156));
    this->map_.push_back(cv::Vec3b(254, 189, 157));
    this->map_.push_back(cv::Vec3b(254, 190, 159));
    this->map_.push_back(cv::Vec3b(254, 191, 160));
    this->map_.push_back(cv::Vec3b(254, 192, 162));
    this->map_.push_back(cv::Vec3b(254, 193, 163));
    this->map_.push_back(cv::Vec3b(254, 194, 164));
    this->map_.push_back(cv::Vec3b(253, 195, 166));
    this->map_.push_back(cv::Vec3b(253, 196, 167));
    this->map_.push_back(cv::Vec3b(253, 197, 168));
    this->map_.push_back(cv::Vec3b(253, 198, 170));
    this->map_.push_back(cv::Vec3b(252, 199, 171));
    this->map_.push_back(cv::Vec3b(252, 200, 172));
    this->map_.push_back(cv::Vec3b(252, 201, 174));
    this->map_.push_back(cv::Vec3b(251, 202, 175));
    this->map_.push_back(cv::Vec3b(251, 203, 176));
    this->map_.push_back(cv::Vec3b(251, 203, 178));
    this->map_.push_back(cv::Vec3b(250, 204, 179));
    this->map_.push_back(cv::Vec3b(250, 205, 180));
    this->map_.push_back(cv::Vec3b(249, 206, 182));
    this->map_.push_back(cv::Vec3b(249, 207, 183));
    this->map_.push_back(cv::Vec3b(248, 207, 184));
    this->map_.push_back(cv::Vec3b(248, 208, 185));
    this->map_.push_back(cv::Vec3b(247, 209, 187));
    this->map_.push_back(cv::Vec3b(246, 209, 188));
    this->map_.push_back(cv::Vec3b(246, 210, 189));
    this->map_.push_back(cv::Vec3b(245, 211, 190));
    this->map_.push_back(cv::Vec3b(245, 211, 192));
    this->map_.push_back(cv::Vec3b(244, 212, 193));
    this->map_.push_back(cv::Vec3b(243, 212, 194));
    this->map_.push_back(cv::Vec3b(242, 213, 195));
    this->map_.push_back(cv::Vec3b(242, 213, 197));
    this->map_.push_back(cv::Vec3b(241, 214, 198));
    this->map_.push_back(cv::Vec3b(240, 214, 199));
    this->map_.push_back(cv::Vec3b(239, 215, 200));
    this->map_.push_back(cv::Vec3b(238, 215, 201));
    this->map_.push_back(cv::Vec3b(238, 216, 202));
    this->map_.push_back(cv::Vec3b(237, 216, 204));
    this->map_.push_back(cv::Vec3b(236, 217, 205));
    this->map_.push_back(cv::Vec3b(235, 217, 206));
    this->map_.push_back(cv::Vec3b(234, 217, 207));
    this->map_.push_back(cv::Vec3b(233, 218, 208));
    this->map_.push_back(cv::Vec3b(232, 218, 209));
    this->map_.push_back(cv::Vec3b(231, 218, 210));
    this->map_.push_back(cv::Vec3b(230, 219, 211));
    this->map_.push_back(cv::Vec3b(229, 219, 213));
    this->map_.push_back(cv::Vec3b(228, 219, 214));
    this->map_.push_back(cv::Vec3b(226, 219, 215));
    this->map_.push_back(cv::Vec3b(225, 219, 216));
    this->map_.push_back(cv::Vec3b(224, 220, 217));
    this->map_.push_back(cv::Vec3b(223, 220, 218));
    this->map_.push_back(cv::Vec3b(222, 220, 219));
    this->map_.push_back(cv::Vec3b(221, 220, 220));
    this->map_.push_back(cv::Vec3b(219, 220, 221));
    this->map_.push_back(cv::Vec3b(218, 219, 222));
    this->map_.push_back(cv::Vec3b(217, 219, 223));
    this->map_.push_back(cv::Vec3b(215, 218, 224));
    this->map_.push_back(cv::Vec3b(214, 218, 225));
    this->map_.push_back(cv::Vec3b(212, 217, 226));
    this->map_.push_back(cv::Vec3b(211, 217, 227));
    this->map_.push_back(cv::Vec3b(209, 216, 228));
    this->map_.push_back(cv::Vec3b(208, 216, 229));
    this->map_.push_back(cv::Vec3b(207, 215, 230));
    this->map_.push_back(cv::Vec3b(205, 214, 231));
    this->map_.push_back(cv::Vec3b(204, 214, 231));
    this->map_.push_back(cv::Vec3b(202, 213, 232));
    this->map_.push_back(cv::Vec3b(201, 212, 233));
    this->map_.push_back(cv::Vec3b(199, 211, 234));
    this->map_.push_back(cv::Vec3b(198, 211, 235));
    this->map_.push_back(cv::Vec3b(196, 210, 236));
    this->map_.push_back(cv::Vec3b(195, 209, 236));
    this->map_.push_back(cv::Vec3b(193, 208, 237));
    this->map_.push_back(cv::Vec3b(192, 207, 237));
    this->map_.push_back(cv::Vec3b(190, 207, 238));
    this->map_.push_back(cv::Vec3b(188, 206, 239));
    this->map_.push_back(cv::Vec3b(187, 205, 239));
    this->map_.push_back(cv::Vec3b(185, 204, 240));
    this->map_.push_back(cv::Vec3b(184, 203, 241));
    this->map_.push_back(cv::Vec3b(182, 202, 241));
    this->map_.push_back(cv::Vec3b(181, 201, 242));
    this->map_.push_back(cv::Vec3b(179, 200, 242));
    this->map_.push_back(cv::Vec3b(178, 199, 242));
    this->map_.push_back(cv::Vec3b(176, 198, 243));
    this->map_.push_back(cv::Vec3b(175, 197, 243));
    this->map_.push_back(cv::Vec3b(173, 196, 244));
    this->map_.push_back(cv::Vec3b(171, 195, 244));
    this->map_.push_back(cv::Vec3b(170, 194, 244));
    this->map_.push_back(cv::Vec3b(168, 193, 245));
    this->map_.push_back(cv::Vec3b(167, 192, 245));
    this->map_.push_back(cv::Vec3b(165, 191, 245));
    this->map_.push_back(cv::Vec3b(164, 189, 246));
    this->map_.push_back(cv::Vec3b(162, 188, 246));
    this->map_.push_back(cv::Vec3b(160, 187, 246));
    this->map_.push_back(cv::Vec3b(159, 186, 246));
    this->map_.push_back(cv::Vec3b(157, 185, 246));
    this->map_.push_back(cv::Vec3b(156, 183, 246));
    this->map_.push_back(cv::Vec3b(154, 182, 246));
    this->map_.push_back(cv::Vec3b(152, 181, 247));
    this->map_.push_back(cv::Vec3b(151, 179, 247));
    this->map_.push_back(cv::Vec3b(149, 178, 247));
    this->map_.push_back(cv::Vec3b(148, 177, 247));
    this->map_.push_back(cv::Vec3b(146, 176, 247));
    this->map_.push_back(cv::Vec3b(145, 174, 247));
    this->map_.push_back(cv::Vec3b(143, 173, 247));
    this->map_.push_back(cv::Vec3b(141, 171, 246));
    this->map_.push_back(cv::Vec3b(140, 170, 246));
    this->map_.push_back(cv::Vec3b(138, 169, 246));
    this->map_.push_back(cv::Vec3b(137, 167, 246));
    this->map_.push_back(cv::Vec3b(135, 166, 246));
    this->map_.push_back(cv::Vec3b(134, 164, 246));
    this->map_.push_back(cv::Vec3b(132, 163, 246));
    this->map_.push_back(cv::Vec3b(130, 161, 245));
    this->map_.push_back(cv::Vec3b(129, 160, 245));
    this->map_.push_back(cv::Vec3b(127, 158, 245));
    this->map_.push_back(cv::Vec3b(126, 157, 244));
    this->map_.push_back(cv::Vec3b(124, 155, 244));
    this->map_.push_back(cv::Vec3b(123, 154, 244));
    this->map_.push_back(cv::Vec3b(121, 152, 243));
    this->map_.push_back(cv::Vec3b(120, 150, 243));
    this->map_.push_back(cv::Vec3b(118, 149, 243));
    this->map_.push_back(cv::Vec3b(117, 147, 242));
    this->map_.push_back(cv::Vec3b(115, 145, 242));
    this->map_.push_back(cv::Vec3b(114, 144, 241));
    this->map_.push_back(cv::Vec3b(112, 142, 241));
    this->map_.push_back(cv::Vec3b(111, 141, 240));
    this->map_.push_back(cv::Vec3b(109, 139, 240));
    this->map_.push_back(cv::Vec3b(108, 137, 239));
    this->map_.push_back(cv::Vec3b(106, 135, 238));
    this->map_.push_back(cv::Vec3b(105, 134, 238));
    this->map_.push_back(cv::Vec3b(103, 132, 237));
    this->map_.push_back(cv::Vec3b(102, 130, 236));
    this->map_.push_back(cv::Vec3b(100, 128, 236));
    this->map_.push_back(cv::Vec3b(99, 127, 235));
    this->map_.push_back(cv::Vec3b(97, 125, 234));
    this->map_.push_back(cv::Vec3b(96, 123, 234));
    this->map_.push_back(cv::Vec3b(94, 121, 233));
    this->map_.push_back(cv::Vec3b(93, 119, 232));
    this->map_.push_back(cv::Vec3b(92, 117, 231));
    this->map_.push_back(cv::Vec3b(90, 116, 230));
    this->map_.push_back(cv::Vec3b(89, 114, 230));
    this->map_.push_back(cv::Vec3b(87, 112, 229));
    this->map_.push_back(cv::Vec3b(86, 110, 228));
    this->map_.push_back(cv::Vec3b(84, 108, 227));
    this->map_.push_back(cv::Vec3b(83, 106, 226));
    this->map_.push_back(cv::Vec3b(82, 104, 225));
    this->map_.push_back(cv::Vec3b(80, 102, 224));
    this->map_.push_back(cv::Vec3b(79, 100, 223));
    this->map_.push_back(cv::Vec3b(78, 98, 222));
    this->map_.push_back(cv::Vec3b(76, 96, 221));
    this->map_.push_back(cv::Vec3b(75, 94, 220));
    this->map_.push_back(cv::Vec3b(74, 92, 219));
    this->map_.push_back(cv::Vec3b(72, 90, 218));
    this->map_.push_back(cv::Vec3b(71, 88, 217));
    this->map_.push_back(cv::Vec3b(70, 86, 216));
    this->map_.push_back(cv::Vec3b(68, 84, 215));
    this->map_.push_back(cv::Vec3b(67, 82, 214));
    this->map_.push_back(cv::Vec3b(66, 79, 212));
    this->map_.push_back(cv::Vec3b(64, 77, 211));
    this->map_.push_back(cv::Vec3b(63, 75, 210));
    this->map_.push_back(cv::Vec3b(62, 73, 209));
    this->map_.push_back(cv::Vec3b(61, 70, 207));
    this->map_.push_back(cv::Vec3b(60, 68, 206));
    this->map_.push_back(cv::Vec3b(58, 66, 205));
    this->map_.push_back(cv::Vec3b(57, 63, 204));
    this->map_.push_back(cv::Vec3b(56, 61, 202));
    this->map_.push_back(cv::Vec3b(55, 59, 201));
    this->map_.push_back(cv::Vec3b(53, 56, 200));
    this->map_.push_back(cv::Vec3b(52, 53, 198));
    this->map_.push_back(cv::Vec3b(51, 50, 197));
    this->map_.push_back(cv::Vec3b(50, 48, 196));
    this->map_.push_back(cv::Vec3b(49, 45, 194));
    this->map_.push_back(cv::Vec3b(48, 42, 193));
    this->map_.push_back(cv::Vec3b(46, 40, 191));
    this->map_.push_back(cv::Vec3b(45, 35, 190));
    this->map_.push_back(cv::Vec3b(44, 31, 188));
    this->map_.push_back(cv::Vec3b(43, 26, 187));
    this->map_.push_back(cv::Vec3b(42, 22, 185));
    this->map_.push_back(cv::Vec3b(41, 17, 184));
    this->map_.push_back(cv::Vec3b(40, 13, 182));
    this->map_.push_back(cv::Vec3b(39, 8, 181));
    this->map_.push_back(cv::Vec3b(38, 3, 179));
  }
  
private:
  ColorMapCoolWarm(const ColorMapCoolWarm<Dtype>& m);
  void operator=(const ColorMapCoolWarm<Dtype>& m);
};


} //ns cv
} //ns rv

#endif
