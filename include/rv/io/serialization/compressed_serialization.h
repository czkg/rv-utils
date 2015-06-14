#ifndef RV_IO_COMPRESSED_SERIALIZATION_H
#define RV_IO_COMPRESSED_SERIALIZATION_H

#include "serialization.h"

#include <stdio.h>
#include <zlib.h>

namespace rv {
namespace io {

class CompressedSerializationOut : public SerializationOut {
public:
  CompressedSerializationOut(const std::string& path) : SerializationOut(path) {
    f_ = gzopen(path.c_str(), "wb");
  }

  virtual ~CompressedSerializationOut() {
    gzclose(f_);
  }

  virtual SerializationOut& operator<<(const bool& v) {
    gzwrite(f_, &v, sizeof(bool));
    return (*this);
  }
  virtual SerializationOut& operator<<(const char& v) {
    gzwrite(f_, &v, sizeof(char));
    return (*this);
  }
  virtual SerializationOut& operator<<(const int& v) {
    gzwrite(f_, &v, sizeof(int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned int& v) {
    gzwrite(f_, &v, sizeof(unsigned int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const long int& v) {
    gzwrite(f_, &v, sizeof(long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned long int& v) {
    gzwrite(f_, &v, sizeof(unsigned long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const long long int& v) {
    gzwrite(f_, &v, sizeof(long long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned long long int& v) {
    gzwrite(f_, &v, sizeof(unsigned long long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const float& v) {
    gzwrite(f_, &v, sizeof(float));
    return (*this);
  }
  virtual SerializationOut& operator<<(const double& v) {
    gzwrite(f_, &v, sizeof(double));
    return (*this);
  }

protected:
  gzFile f_;
};



class CompressedSerializationIn : public SerializationIn {
public:
  CompressedSerializationIn(const std::string& path) : SerializationIn(path) {
    f_ = gzopen(path.c_str(), "rb");  
  }

  virtual ~CompressedSerializationIn() {
    gzclose(f_);
  }

  virtual SerializationIn& operator>>(bool& v) {
    gzread(f_, &v, sizeof(bool));
    return (*this);
  }
  virtual SerializationIn& operator>>(char& v) {
    gzread(f_, &v, sizeof(char));
    return (*this);
  }
  virtual SerializationIn& operator>>(int& v) {
    gzread(f_, &v, sizeof(int));
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned int& v) {
    gzread(f_, &v, sizeof(unsigned int));
    return (*this);
  }
  virtual SerializationIn& operator>>(long int& v) {
    gzread(f_, &v, sizeof(long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned long int& v) {
    gzread(f_, &v, sizeof(unsigned long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(long long int& v) {
    gzread(f_, &v, sizeof(long long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned long long int& v) {
    gzread(f_, &v, sizeof(unsigned long long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(float& v) {
    gzread(f_, &v, sizeof(float));
    return (*this);
  }
  virtual SerializationIn& operator>>(double& v) {
    gzread(f_, &v, sizeof(double));
    return (*this);
  }

protected:
  gzFile f_;
};




} //ns io
} //ns rv


#endif // RV_IO_BINARY_SERIALIZATION_H

