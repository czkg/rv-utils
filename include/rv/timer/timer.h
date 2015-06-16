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

#ifndef RV_TIMER_TIMER_H
#define RV_TIMER_TIMER_H

#include <iostream>
#include <map>

#include <rv/stat/cumulative.h>


typedef float millisec_t;


namespace rv {
namespace timer {

  
class Timer {
public:
  Timer() {}
  virtual ~Timer() {}
  
  virtual void start() = 0;
  virtual millisec_t stop() = 0;

  virtual void clear() {
    stat_.reset();
  }

  virtual size_t n() { 
    return stat_.n();
  }

  virtual millisec_t total() const {
    return stat_.sum();
  }
  
  virtual millisec_t mean() const {
    return stat_.mean();
  }
  
protected:
    rv::stat::CumulativeStatistics<double> stat_;
};


class BatchedTimer {
public:
  
  virtual void start(const std::string& id) = 0;
  virtual millisec_t stop(const std::string& id) = 0;

  virtual void clear(const std::string& id) {
    stats_[id].reset();
  }

  virtual size_t n(const std::string& id) { 
    return stats_[id].n();
  }

  virtual millisec_t total(const std::string& id) {
    return stats_[id].sum();
  }
  
  virtual millisec_t mean(const std::string& id) {
    return stats_[id].mean();
  }
  
  virtual void print(std::ostream& out) {
    for(std::map<std::string, rv::stat::CumulativeStatistics<double> >::iterator it = stats_.begin(); it != stats_.end(); ++it) {
      std::string id = it->first;
      size_t n = it->second.n();
      millisec_t sum = it->second.sum();
      millisec_t mean = it->second.mean();
      
      out << id << ": " << sum * 1e-3 << " [s] in total for " << n << " timings => mean = " << mean * 1e-3 << " [s]" << std::endl;
    }
  }
  
protected:
  BatchedTimer() {}
  virtual ~BatchedTimer() {}
  
protected:
    std::map<std::string, rv::stat::CumulativeStatistics<double> > stats_;
};


} //ns timer
} //ns rv

#endif
