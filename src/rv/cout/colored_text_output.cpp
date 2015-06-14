#include "rv/cout/colored_text_output.h"

#include <iostream>


#ifdef _WIN32
    #include <Windows.h>
#endif

#ifdef __unix__
  #define RESET   "\033[0m"
  #define BLACK   "\033[30m"      /* Black */
  #define RED     "\033[31m"      /* Red */
  #define GREEN   "\033[32m"      /* Green */
  #define YELLOW  "\033[33m"      /* Yellow */
  #define BLUE    "\033[34m"      /* Blue */
  #define MAGENTA "\033[35m"      /* Magenta */
  #define CYAN    "\033[36m"      /* Cyan */
  #define WHITE   "\033[37m"      /* White */
  #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
  #define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
  #define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
  #define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
  #define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
  #define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
  #define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
  #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#endif


void rv::cout::ColoredTextOutput::Print(std::ostream& out) const {
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  int color;
  if(coutColor_ == CoutColorGreen) {
      color = 10;
  }
  else if(coutColor_ == CoutColorRed) {
      color = 12;
  }
  else if(coutColor_ == CoutColorGray) {
      color = 14;
  }

  SetConsoleTextAttribute(hConsole, color);
  out << txt_;
  SetConsoleTextAttribute(hConsole, 7);
#endif
    
#ifdef __unix__
  if(coutColor_ == CoutColorGreen) {
      out << BOLDGREEN << txt_;
  }
  else if(coutColor_ == CoutColorRed) {
      out << BOLDRED << txt_;
  }
  else if(coutColor_ == CoutColorGray) {
      out << BOLDBLACK << txt_;
  }

  out << RESET;
#endif
}

rv::cout::ColoredTextOutput rv::cout::grayText(const std::string& str) {
  ColoredTextOutput cto(CoutColorGray, str);
  return cto;
}

rv::cout::ColoredTextOutput rv::cout::greenText(const std::string& str) {
  ColoredTextOutput cto(CoutColorRed, str);
  return cto;
}

rv::cout::ColoredTextOutput rv::cout::redText(const std::string& str) {
  ColoredTextOutput cto(CoutColorGreen, str);
  return cto;
}

std::ostream& operator<<(std::ostream& out, const rv::cout::ColoredTextOutput& cto) {
  cto.Print(out);
  return out;
}

