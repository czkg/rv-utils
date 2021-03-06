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

#ifndef RV_OCV_COLORMAP_GNUPLOT_H
#define RV_OCV_COLORMAP_GNUPLOT_H

#include "colormap.h"

namespace rv {
namespace ocv {

template <typename Dtype>
class ColorMapGnuPlot : public ColorMap<Dtype> {
public:
  static ColorMapGnuPlot<Dtype>& i() {
    static ColorMapGnuPlot<Dtype> instance;
    return instance;
  }
  
  virtual std::string name() const {
    return "gnuplot";
  }
  
protected:
  ColorMapGnuPlot() {
    //init colors 
    this->map_.push_back(cv::Vec3b(0, 0, 0));
    this->map_.push_back(cv::Vec3b(6, 0, 15));
    this->map_.push_back(cv::Vec3b(12, 0, 22));
    this->map_.push_back(cv::Vec3b(18, 0, 27));
    this->map_.push_back(cv::Vec3b(25, 0, 31));
    this->map_.push_back(cv::Vec3b(31, 0, 35));
    this->map_.push_back(cv::Vec3b(37, 0, 39));
    this->map_.push_back(cv::Vec3b(43, 0, 42));
    this->map_.push_back(cv::Vec3b(49, 0, 45));
    this->map_.push_back(cv::Vec3b(56, 0, 47));
    this->map_.push_back(cv::Vec3b(62, 0, 50));
    this->map_.push_back(cv::Vec3b(68, 0, 52));
    this->map_.push_back(cv::Vec3b(74, 0, 55));
    this->map_.push_back(cv::Vec3b(80, 0, 57));
    this->map_.push_back(cv::Vec3b(86, 0, 59));
    this->map_.push_back(cv::Vec3b(92, 0, 61));
    this->map_.push_back(cv::Vec3b(97, 0, 63));
    this->map_.push_back(cv::Vec3b(103, 0, 65));
    this->map_.push_back(cv::Vec3b(109, 0, 67));
    this->map_.push_back(cv::Vec3b(115, 0, 69));
    this->map_.push_back(cv::Vec3b(120, 0, 71));
    this->map_.push_back(cv::Vec3b(126, 0, 73));
    this->map_.push_back(cv::Vec3b(131, 0, 74));
    this->map_.push_back(cv::Vec3b(136, 0, 76));
    this->map_.push_back(cv::Vec3b(142, 0, 78));
    this->map_.push_back(cv::Vec3b(147, 0, 79));
    this->map_.push_back(cv::Vec3b(152, 0, 81));
    this->map_.push_back(cv::Vec3b(157, 0, 82));
    this->map_.push_back(cv::Vec3b(162, 0, 84));
    this->map_.push_back(cv::Vec3b(167, 0, 85));
    this->map_.push_back(cv::Vec3b(171, 0, 87));
    this->map_.push_back(cv::Vec3b(176, 0, 88));
    this->map_.push_back(cv::Vec3b(180, 0, 90));
    this->map_.push_back(cv::Vec3b(185, 0, 91));
    this->map_.push_back(cv::Vec3b(189, 0, 93));
    this->map_.push_back(cv::Vec3b(193, 0, 94));
    this->map_.push_back(cv::Vec3b(197, 0, 95));
    this->map_.push_back(cv::Vec3b(201, 0, 97));
    this->map_.push_back(cv::Vec3b(205, 0, 98));
    this->map_.push_back(cv::Vec3b(209, 0, 99));
    this->map_.push_back(cv::Vec3b(212, 0, 100));
    this->map_.push_back(cv::Vec3b(215, 1, 102));
    this->map_.push_back(cv::Vec3b(219, 1, 103));
    this->map_.push_back(cv::Vec3b(222, 1, 104));
    this->map_.push_back(cv::Vec3b(225, 1, 105));
    this->map_.push_back(cv::Vec3b(228, 1, 107));
    this->map_.push_back(cv::Vec3b(230, 1, 108));
    this->map_.push_back(cv::Vec3b(233, 1, 109));
    this->map_.push_back(cv::Vec3b(236, 1, 110));
    this->map_.push_back(cv::Vec3b(238, 1, 111));
    this->map_.push_back(cv::Vec3b(240, 1, 112));
    this->map_.push_back(cv::Vec3b(242, 2, 114));
    this->map_.push_back(cv::Vec3b(244, 2, 115));
    this->map_.push_back(cv::Vec3b(246, 2, 116));
    this->map_.push_back(cv::Vec3b(247, 2, 117));
    this->map_.push_back(cv::Vec3b(249, 2, 118));
    this->map_.push_back(cv::Vec3b(250, 2, 119));
    this->map_.push_back(cv::Vec3b(251, 2, 120));
    this->map_.push_back(cv::Vec3b(252, 3, 121));
    this->map_.push_back(cv::Vec3b(253, 3, 122));
    this->map_.push_back(cv::Vec3b(253, 3, 123));
    this->map_.push_back(cv::Vec3b(254, 3, 124));
    this->map_.push_back(cv::Vec3b(254, 3, 125));
    this->map_.push_back(cv::Vec3b(254, 3, 126));
    this->map_.push_back(cv::Vec3b(254, 4, 127));
    this->map_.push_back(cv::Vec3b(254, 4, 128));
    this->map_.push_back(cv::Vec3b(254, 4, 129));
    this->map_.push_back(cv::Vec3b(254, 4, 130));
    this->map_.push_back(cv::Vec3b(253, 4, 131));
    this->map_.push_back(cv::Vec3b(252, 5, 132));
    this->map_.push_back(cv::Vec3b(251, 5, 133));
    this->map_.push_back(cv::Vec3b(250, 5, 134));
    this->map_.push_back(cv::Vec3b(249, 5, 135));
    this->map_.push_back(cv::Vec3b(248, 5, 136));
    this->map_.push_back(cv::Vec3b(246, 6, 137));
    this->map_.push_back(cv::Vec3b(245, 6, 138));
    this->map_.push_back(cv::Vec3b(243, 6, 139));
    this->map_.push_back(cv::Vec3b(241, 7, 140));
    this->map_.push_back(cv::Vec3b(239, 7, 141));
    this->map_.push_back(cv::Vec3b(237, 7, 141));
    this->map_.push_back(cv::Vec3b(234, 7, 142));
    this->map_.push_back(cv::Vec3b(232, 8, 143));
    this->map_.push_back(cv::Vec3b(229, 8, 144));
    this->map_.push_back(cv::Vec3b(226, 8, 145));
    this->map_.push_back(cv::Vec3b(223, 9, 146));
    this->map_.push_back(cv::Vec3b(220, 9, 147));
    this->map_.push_back(cv::Vec3b(217, 9, 148));
    this->map_.push_back(cv::Vec3b(214, 10, 148));
    this->map_.push_back(cv::Vec3b(210, 10, 149));
    this->map_.push_back(cv::Vec3b(207, 10, 150));
    this->map_.push_back(cv::Vec3b(203, 11, 151));
    this->map_.push_back(cv::Vec3b(199, 11, 152));
    this->map_.push_back(cv::Vec3b(195, 11, 153));
    this->map_.push_back(cv::Vec3b(191, 12, 153));
    this->map_.push_back(cv::Vec3b(187, 12, 154));
    this->map_.push_back(cv::Vec3b(183, 13, 155));
    this->map_.push_back(cv::Vec3b(178, 13, 156));
    this->map_.push_back(cv::Vec3b(174, 14, 157));
    this->map_.push_back(cv::Vec3b(169, 14, 158));
    this->map_.push_back(cv::Vec3b(164, 14, 158));
    this->map_.push_back(cv::Vec3b(159, 15, 159));
    this->map_.push_back(cv::Vec3b(154, 15, 160));
    this->map_.push_back(cv::Vec3b(149, 16, 161));
    this->map_.push_back(cv::Vec3b(144, 16, 162));
    this->map_.push_back(cv::Vec3b(139, 17, 162));
    this->map_.push_back(cv::Vec3b(134, 17, 163));
    this->map_.push_back(cv::Vec3b(128, 18, 164));
    this->map_.push_back(cv::Vec3b(123, 18, 165));
    this->map_.push_back(cv::Vec3b(117, 19, 165));
    this->map_.push_back(cv::Vec3b(112, 19, 166));
    this->map_.push_back(cv::Vec3b(106, 20, 167));
    this->map_.push_back(cv::Vec3b(100, 21, 168));
    this->map_.push_back(cv::Vec3b(95, 21, 168));
    this->map_.push_back(cv::Vec3b(89, 22, 169));
    this->map_.push_back(cv::Vec3b(83, 22, 170));
    this->map_.push_back(cv::Vec3b(77, 23, 171));
    this->map_.push_back(cv::Vec3b(71, 24, 171));
    this->map_.push_back(cv::Vec3b(65, 24, 172));
    this->map_.push_back(cv::Vec3b(59, 25, 173));
    this->map_.push_back(cv::Vec3b(53, 25, 174));
    this->map_.push_back(cv::Vec3b(46, 26, 174));
    this->map_.push_back(cv::Vec3b(40, 27, 175));
    this->map_.push_back(cv::Vec3b(34, 27, 176));
    this->map_.push_back(cv::Vec3b(28, 28, 177));
    this->map_.push_back(cv::Vec3b(21, 29, 177));
    this->map_.push_back(cv::Vec3b(15, 30, 178));
    this->map_.push_back(cv::Vec3b(9, 30, 179));
    this->map_.push_back(cv::Vec3b(3, 31, 179));
    this->map_.push_back(cv::Vec3b(0, 32, 180));
    this->map_.push_back(cv::Vec3b(0, 33, 181));
    this->map_.push_back(cv::Vec3b(0, 33, 182));
    this->map_.push_back(cv::Vec3b(0, 34, 182));
    this->map_.push_back(cv::Vec3b(0, 35, 183));
    this->map_.push_back(cv::Vec3b(0, 36, 184));
    this->map_.push_back(cv::Vec3b(0, 37, 184));
    this->map_.push_back(cv::Vec3b(0, 37, 185));
    this->map_.push_back(cv::Vec3b(0, 38, 186));
    this->map_.push_back(cv::Vec3b(0, 39, 186));
    this->map_.push_back(cv::Vec3b(0, 40, 187));
    this->map_.push_back(cv::Vec3b(0, 41, 188));
    this->map_.push_back(cv::Vec3b(0, 42, 188));
    this->map_.push_back(cv::Vec3b(0, 43, 189));
    this->map_.push_back(cv::Vec3b(0, 44, 190));
    this->map_.push_back(cv::Vec3b(0, 44, 190));
    this->map_.push_back(cv::Vec3b(0, 45, 191));
    this->map_.push_back(cv::Vec3b(0, 46, 192));
    this->map_.push_back(cv::Vec3b(0, 47, 192));
    this->map_.push_back(cv::Vec3b(0, 48, 193));
    this->map_.push_back(cv::Vec3b(0, 49, 194));
    this->map_.push_back(cv::Vec3b(0, 50, 194));
    this->map_.push_back(cv::Vec3b(0, 51, 195));
    this->map_.push_back(cv::Vec3b(0, 52, 196));
    this->map_.push_back(cv::Vec3b(0, 54, 196));
    this->map_.push_back(cv::Vec3b(0, 55, 197));
    this->map_.push_back(cv::Vec3b(0, 56, 198));
    this->map_.push_back(cv::Vec3b(0, 57, 198));
    this->map_.push_back(cv::Vec3b(0, 58, 199));
    this->map_.push_back(cv::Vec3b(0, 59, 200));
    this->map_.push_back(cv::Vec3b(0, 60, 200));
    this->map_.push_back(cv::Vec3b(0, 61, 201));
    this->map_.push_back(cv::Vec3b(0, 62, 201));
    this->map_.push_back(cv::Vec3b(0, 64, 202));
    this->map_.push_back(cv::Vec3b(0, 65, 203));
    this->map_.push_back(cv::Vec3b(0, 66, 203));
    this->map_.push_back(cv::Vec3b(0, 67, 204));
    this->map_.push_back(cv::Vec3b(0, 69, 205));
    this->map_.push_back(cv::Vec3b(0, 70, 205));
    this->map_.push_back(cv::Vec3b(0, 71, 206));
    this->map_.push_back(cv::Vec3b(0, 72, 206));
    this->map_.push_back(cv::Vec3b(0, 74, 207));
    this->map_.push_back(cv::Vec3b(0, 75, 208));
    this->map_.push_back(cv::Vec3b(0, 76, 208));
    this->map_.push_back(cv::Vec3b(0, 78, 209));
    this->map_.push_back(cv::Vec3b(0, 79, 210));
    this->map_.push_back(cv::Vec3b(0, 81, 210));
    this->map_.push_back(cv::Vec3b(0, 82, 211));
    this->map_.push_back(cv::Vec3b(0, 83, 211));
    this->map_.push_back(cv::Vec3b(0, 85, 212));
    this->map_.push_back(cv::Vec3b(0, 86, 213));
    this->map_.push_back(cv::Vec3b(0, 88, 213));
    this->map_.push_back(cv::Vec3b(0, 89, 214));
    this->map_.push_back(cv::Vec3b(0, 91, 214));
    this->map_.push_back(cv::Vec3b(0, 92, 215));
    this->map_.push_back(cv::Vec3b(0, 94, 216));
    this->map_.push_back(cv::Vec3b(0, 95, 216));
    this->map_.push_back(cv::Vec3b(0, 97, 217));
    this->map_.push_back(cv::Vec3b(0, 98, 217));
    this->map_.push_back(cv::Vec3b(0, 100, 218));
    this->map_.push_back(cv::Vec3b(0, 102, 218));
    this->map_.push_back(cv::Vec3b(0, 103, 219));
    this->map_.push_back(cv::Vec3b(0, 105, 220));
    this->map_.push_back(cv::Vec3b(0, 107, 220));
    this->map_.push_back(cv::Vec3b(0, 108, 221));
    this->map_.push_back(cv::Vec3b(0, 110, 221));
    this->map_.push_back(cv::Vec3b(0, 112, 222));
    this->map_.push_back(cv::Vec3b(0, 114, 222));
    this->map_.push_back(cv::Vec3b(0, 115, 223));
    this->map_.push_back(cv::Vec3b(0, 117, 224));
    this->map_.push_back(cv::Vec3b(0, 119, 224));
    this->map_.push_back(cv::Vec3b(0, 121, 225));
    this->map_.push_back(cv::Vec3b(0, 123, 225));
    this->map_.push_back(cv::Vec3b(0, 124, 226));
    this->map_.push_back(cv::Vec3b(0, 126, 226));
    this->map_.push_back(cv::Vec3b(0, 128, 227));
    this->map_.push_back(cv::Vec3b(0, 130, 228));
    this->map_.push_back(cv::Vec3b(0, 132, 228));
    this->map_.push_back(cv::Vec3b(0, 134, 229));
    this->map_.push_back(cv::Vec3b(0, 136, 229));
    this->map_.push_back(cv::Vec3b(0, 138, 230));
    this->map_.push_back(cv::Vec3b(0, 140, 230));
    this->map_.push_back(cv::Vec3b(0, 142, 231));
    this->map_.push_back(cv::Vec3b(0, 144, 231));
    this->map_.push_back(cv::Vec3b(0, 146, 232));
    this->map_.push_back(cv::Vec3b(0, 148, 233));
    this->map_.push_back(cv::Vec3b(0, 150, 233));
    this->map_.push_back(cv::Vec3b(0, 152, 234));
    this->map_.push_back(cv::Vec3b(0, 154, 234));
    this->map_.push_back(cv::Vec3b(0, 157, 235));
    this->map_.push_back(cv::Vec3b(0, 159, 235));
    this->map_.push_back(cv::Vec3b(0, 161, 236));
    this->map_.push_back(cv::Vec3b(0, 163, 236));
    this->map_.push_back(cv::Vec3b(0, 165, 237));
    this->map_.push_back(cv::Vec3b(0, 168, 237));
    this->map_.push_back(cv::Vec3b(0, 170, 238));
    this->map_.push_back(cv::Vec3b(0, 172, 238));
    this->map_.push_back(cv::Vec3b(0, 175, 239));
    this->map_.push_back(cv::Vec3b(0, 177, 240));
    this->map_.push_back(cv::Vec3b(0, 179, 240));
    this->map_.push_back(cv::Vec3b(0, 182, 241));
    this->map_.push_back(cv::Vec3b(0, 184, 241));
    this->map_.push_back(cv::Vec3b(0, 187, 242));
    this->map_.push_back(cv::Vec3b(0, 189, 242));
    this->map_.push_back(cv::Vec3b(0, 192, 243));
    this->map_.push_back(cv::Vec3b(0, 194, 243));
    this->map_.push_back(cv::Vec3b(0, 197, 244));
    this->map_.push_back(cv::Vec3b(0, 199, 244));
    this->map_.push_back(cv::Vec3b(0, 202, 245));
    this->map_.push_back(cv::Vec3b(0, 204, 245));
    this->map_.push_back(cv::Vec3b(0, 207, 246));
    this->map_.push_back(cv::Vec3b(0, 209, 246));
    this->map_.push_back(cv::Vec3b(0, 212, 247));
    this->map_.push_back(cv::Vec3b(0, 215, 247));
    this->map_.push_back(cv::Vec3b(0, 217, 248));
    this->map_.push_back(cv::Vec3b(0, 220, 248));
    this->map_.push_back(cv::Vec3b(0, 223, 249));
    this->map_.push_back(cv::Vec3b(0, 226, 249));
    this->map_.push_back(cv::Vec3b(0, 228, 250));
    this->map_.push_back(cv::Vec3b(0, 231, 250));
    this->map_.push_back(cv::Vec3b(0, 234, 251));
    this->map_.push_back(cv::Vec3b(0, 237, 251));
    this->map_.push_back(cv::Vec3b(0, 240, 252));
    this->map_.push_back(cv::Vec3b(0, 243, 252));
    this->map_.push_back(cv::Vec3b(0, 246, 253));
    this->map_.push_back(cv::Vec3b(0, 249, 253));
    this->map_.push_back(cv::Vec3b(0, 252, 254));
    this->map_.push_back(cv::Vec3b(0, 255, 255));
  }
  
private:
  ColorMapGnuPlot(const ColorMapGnuPlot<Dtype>& m);
  void operator=(const ColorMapGnuPlot<Dtype>& m);
};


} //ns cv
} //ns rv

#endif
