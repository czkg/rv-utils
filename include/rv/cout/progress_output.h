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

#ifndef RV_COUT_PROGRESS_OUTPUT_H
#define RV_COUT_PROGRESS_OUTPUT_H

#include <iostream>
#include <boost/format.hpp>

namespace rv {
namespace cout {

class ProgressOutput {
public:
  ProgressOutput(unsigned int max_val, int output_type) :
    val_(0), max_val_(max_val), text_width_(100), output_type_(output_type)
  {}
  
  virtual ~ProgressOutput() {}

  virtual void Reset() {
    val_ = 0;
  }

  virtual const ProgressOutput& operator++(int dummy) {
    if(val_ < max_val_) {
      val_++;
    }
    Print();

    return *this;
  }


private:
  void Print() const {
    float progress = float(val_) / float(max_val_);

    std::string progressStr;
    if(output_type_ == PROGRESS_OUTPUT_PERCENT) {
        progressStr = boost::str(boost::format("%1.2f") % progress);
    }
    else {
        progressStr = boost::str(boost::format("%d/%d") % val_ % max_val_);
    }

    int fixText = progressStr.size(); //4 percent, 2 |, 2 spaces
    int starText = text_width_ - fixText;

    int nStars = starText * progress;
    int nVoid = starText - nStars;

    if(val_ > 1) {
        std::cout << "\r";
    }
    std::cout.flush();
    std::cout << "|";
    for(int i = 0; i < nStars; ++i) {
        std::cout << "*";
    }
    std::cout << " " << progressStr << " ";
    for(int i = 0; i < nVoid; ++i) {
        std::cout << " ";
    }
    std::cout << "|";
    std::cout.flush();

    if(val_ >= max_val_) {
        std::cout << std::endl;
    }
  }
  
public:
  static const int PROGRESS_OUTPUT_PERCENT = 0;
  static const int PROGRESS_OUTPUT_NSAMPLE = 1;
  
private:
  unsigned int val_;
  unsigned int max_val_;

  unsigned int text_width_;

  int output_type_;
};


} //ns cout
} //ns rv

#endif 
