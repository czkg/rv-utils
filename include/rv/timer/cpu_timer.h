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
