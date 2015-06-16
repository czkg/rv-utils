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

