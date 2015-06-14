#ifndef RV_COUT_COLORED_TEXT_OUTPUT_H
#define RV_COUT_COLORED_TEXT_OUTPUT_H

#include <string>

namespace rv {
namespace cout {
  
enum {
  CoutColorRed,
  CoutColorGreen,
  CoutColorGray
};

class ColoredTextOutput {
public:
  ColoredTextOutput(int coutColor, const std::string& txt) : 
      coutColor_(coutColor), txt_(txt) 
  {}
  
  virtual ~ColoredTextOutput() {}

  void Print(std::ostream& out) const;
  
private:
  int coutColor_;
  const std::string txt_;
};


ColoredTextOutput grayText(const std::string& str);
ColoredTextOutput redText(const std::string& str);
ColoredTextOutput greenText(const std::string& str);

} //ns cout
} //ns rv


std::ostream& operator<<(std::ostream& out, const rv::cout::ColoredTextOutput& cto);


#endif