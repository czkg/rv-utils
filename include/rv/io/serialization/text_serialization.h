#ifndef RV_IO_TEXT_SERIALIZATION_H
#define RV_IO_TEXT_SERIALIZATION_H

#include "serialization.h"

#include <fstream>

namespace rv {
namespace io {
  
class TextSerializationOut : public SerializationOut {
public:
  TextSerializationOut(const std::string& path) : SerializationOut(path), 
    f_(path.c_str()) {}
  virtual ~TextSerializationOut() { 
    f_.close();
  }

  virtual SerializationOut& operator<<(const bool& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const char& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const int& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned int& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const long int& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned long int& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const long long int& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned long long int& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const float& v) {
    f_ << v << std::endl;
    return (*this);
  }
  virtual SerializationOut& operator<<(const double& v) {
    f_ << v << std::endl;
    return (*this);
  }

protected:
  std::ofstream f_;
};

class TextSerializationIn : public SerializationIn {
public:
  TextSerializationIn(const std::string& path) : SerializationIn(path), 
    f_(path.c_str()) {}
  virtual ~TextSerializationIn() {
    f_.close();
  }

  virtual SerializationIn& operator>>(bool& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(char& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(int& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned int& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(long int& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned long int& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(long long int& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned long long int& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(float& v) {
    f_ >> v;
    return (*this);
  }
  virtual SerializationIn& operator>>(double& v) {
    f_ >> v;
    return (*this);
  }

protected:
  std::ifstream f_;
};



} //ns io
} //ns rv


#endif
