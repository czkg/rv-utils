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
