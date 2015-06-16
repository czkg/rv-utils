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

#ifndef RV_STAT_CUMULATIVE_H
#define RV_STAT_CUMULATIVE_H

#include <cmath>

namespace rv {
namespace stat {
  
  
template <typename T>
class CumulativeStatistics {
public:
  CumulativeStatistics() { reset(); }
  virtual ~CumulativeStatistics() {}
  
  virtual void reset() {
    k_ = 0;
    sum_ = 0;
    A_km1_ = 0;
    A_k_ = 0;
    Q_km1_ = 0;
    Q_k_ = 0;
  }
  
  virtual void add(T x) {
    k_ += 1;
    
    //sum
    sum_ += x;
    
    //mean
    A_km1_ = A_k_;
    A_k_ = A_km1_ + (x - A_km1_) / T(k_);
    
    //variance
    Q_km1_ = Q_k_;
    Q_k_ = Q_km1_ + (x - A_km1_) * (x - A_k_);
  }
  
  virtual void operator()(T x) {
    add(x);
  }
  
  virtual size_t n() const {
    return k_;
  }
  
  virtual T sum() const {
    return sum_;
  }
  
  virtual T mean() const {
    return A_k_;
  }
  
  virtual T variance() const {
    if(k_ > 1) {
      return Q_k_ / T(k_ - 1.0);
    }
    else {
      return 0;
    }
  }
  
  virtual T std() const {
    return sqrt(variance());
  }
  
  
  static T mean(const std::vector<CumulativeStatistics<T> >& stats) {
    CumulativeStatistics stat;
    for(size_t idx = 0; idx < stats.size(); ++idx) {
      stat.add(stats[idx].mean());
    }
    return stat.mean();
  }
  
  static T variance(const std::vector<CumulativeStatistics<T> >& stats) {
    CumulativeStatistics stat;
    for(size_t idx = 0; idx < stats.size(); ++idx) {
      stat.add(stats[idx].variance());
    }
    return stat.mean();
  }
  
  static T std(const std::vector<CumulativeStatistics<T> >& stats) {
    CumulativeStatistics stat;
    for(size_t idx = 0; idx < stats.size(); ++idx) {
      stat.add(stats[idx].std());
    }
    return stat.mean();
  }
  
private:
  size_t k_;
  T sum_;
  
  T A_km1_;
  T A_k_;
  T Q_km1_;
  T Q_k_;
};


} //ns stat
} //ns rv

#endif
