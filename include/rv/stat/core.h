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

#ifndef RV_STAT_CORE_H
#define RV_STAT_CORE_H

#include <vector>
#include <algorithm>
#include <math.h>


namespace rv {
namespace stat {

  
template <typename T>
T Median(std::vector<T>& values) {
  size_t size = values.size();

  std::sort(values.begin(), values.end());

  if(size % 2 == 0) {
    return (values[size / 2 - 1] + values[size / 2]) / 2;
  } else {
    return values[size / 2];
  }
}


template <typename T>
T Mean(std::vector<T>& values) {
  T m = 0;
  size_t n = values.size();

  for(size_t i = 0; i < n; ++i) {
    m = m + values.at(i);
  }

  return m / n;
}


template <typename T>
T Variance(std::vector<T>& values, T m) {
  T s = 0;

  size_t n = values.size();
  if(n <= 1) {
    return 0;
  }
  
  for(size_t i = 0; i < n; ++i) {
    T val = values.at(i) - m;
    s = s + val * val;
  }

  return s / (n - 1);;
}


template <typename T>
T Variance(std::vector<T>& values) {
  T m = Mean(values);
  return Variance(values, m);
}


template <typename T>
T StandardDeviation(std::vector<T>& values) {
  return std::sqrt(Variance(values));
}


template <typename T>
T StandardDeviation(std::vector<T>& values, T m) {
  return std::sqrt(Variance(values, m));
}


template <typename T>
inline T Min(std::vector<T>& values) {
  return *std::min_element(values.begin(), values.end());
}


template <typename T>
inline T Max(std::vector<T>& values) {
  return *std::max_element(values.begin(), values.end());
}


} //ns stat
} //ns rv

#endif
