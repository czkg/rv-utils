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
