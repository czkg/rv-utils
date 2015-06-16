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

#ifndef RV_IO_BINARY_SERIALIZATION_H
#define RV_IO_BINARY_SERIALIZATION_H

#include "serialization.h"

#include <fstream>

namespace rv {
namespace io {

class BinarySerializationOut : public SerializationOut {
public:
  BinarySerializationOut(const std::string& path) : SerializationOut(path), 
      f_(path.c_str(), std::ios::binary) {}
  virtual ~BinarySerializationOut() {
    f_.close();
  }

  virtual SerializationOut& operator<<(const bool& v) {
    f_.write((char*)&v, sizeof(bool));
    return (*this);
  }
  virtual SerializationOut& operator<<(const char& v) {
    f_.write((char*)&v, sizeof(char));
    return (*this);
  }
  virtual SerializationOut& operator<<(const int& v) {
    f_.write((char*)&v, sizeof(int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned int& v) {
    f_.write((char*)&v, sizeof(unsigned int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const long int& v) {
    f_.write((char*)&v, sizeof(long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned long int& v) {
    f_.write((char*)&v, sizeof(unsigned long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const long long int& v) {
    f_.write((char*)&v, sizeof(long long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const unsigned long long int& v) {
    f_.write((char*)&v, sizeof(unsigned long long int));
    return (*this);
  }
  virtual SerializationOut& operator<<(const float& v) {
    f_.write((char*)&v, sizeof(float));
    return (*this);
  }
  virtual SerializationOut& operator<<(const double& v) {
    f_.write((char*)&v, sizeof(double));
    return (*this);
  }

protected:
  std::ofstream f_;
};

class BinarySerializationIn : public SerializationIn {
public:
  BinarySerializationIn(const std::string& path) : SerializationIn(path), 
    f_(path.c_str(), std::ios::binary) {}
  virtual ~BinarySerializationIn() {
    f_.close();
  }

  virtual SerializationIn& operator>>(bool& v) {
    f_.read((char*)&v, sizeof(bool));
    return (*this);
  }
  virtual SerializationIn& operator>>(char& v) {
    f_.read((char*)&v, sizeof(char));
    return (*this);
  }
  virtual SerializationIn& operator>>(int& v) {
    f_.read((char*)&v, sizeof(int));
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned int& v) {
    f_.read((char*)&v, sizeof(unsigned int));
    return (*this);
  }
  virtual SerializationIn& operator>>(long int& v) {
    f_.read((char*)&v, sizeof(long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned long int& v) {
    f_.read((char*)&v, sizeof(unsigned long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(long long int& v) {
    f_.read((char*)&v, sizeof(long long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(unsigned long long int& v) {
    f_.read((char*)&v, sizeof(unsigned long long int));
    return (*this);
  }
  virtual SerializationIn& operator>>(float& v) {
    f_.read((char*)&v, sizeof(float));
    return (*this);
  }
  virtual SerializationIn& operator>>(double& v) {
    f_.read((char*)&v, sizeof(double));
    return (*this);
  }

protected:
  std::ifstream f_;
};




} //ns io
} //ns rv


#endif // RV_IO_BINARY_SERIALIZATION_H

