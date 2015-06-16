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

#ifndef RV_TIMER_CPU_TIMER_H
#define RV_TIMER_CPU_TIMER_H

#include "timer.h"

#include <boost/timer/timer.hpp>
#include <boost/date_time.hpp>

namespace rv {
namespace timer {

class CpuTimer : public Timer {
public:
  CpuTimer() {}
  virtual ~CpuTimer() {}
  
  virtual void start() {
    timer_.start();
  }
  
  virtual millisec_t stop() {
    boost::timer::nanosecond_type timing = timer_.elapsed().wall;
    millisec_t ms = timing * 1e-6;
    stat_.add(ms);
    
    return ms;
  }
  
private:
  boost::timer::cpu_timer timer_;
};
  

//TODO: make thread safe / omp thread safe
class CpuBatchedTimer : public BatchedTimer {
public:  
  virtual void start(const std::string& id) {
    timers_[id].start();
  }
  
  virtual millisec_t stop(const std::string& id) {
    boost::timer::nanosecond_type timing = timers_[id].elapsed().wall;
    millisec_t ms = timing * 1e-6;
    stats_[id].add(ms);
    
    return ms;
  }
  
  static CpuBatchedTimer& i() {
    static CpuBatchedTimer instance;
    return instance;
  }
  
protected:
  CpuBatchedTimer() {}
  virtual ~CpuBatchedTimer() {}
  
private:
  std::map<std::string, boost::timer::cpu_timer> timers_;
};
  

} //ns timer
} //ns rv

#endif // BATCHEDTIMER_H
