#ifndef RV_TIMER_FPS_H
#define RV_TIMER_FPS_H

#include <boost/date_time.hpp>

namespace rv {
namespace timer {
  
class Fps {
public:
  Fps() {
    n_bumps_ = 0;
    first_ = boost::posix_time::microsec_clock::local_time();
  }
  
  virtual ~Fps() {}
  
  virtual float Bump() {
    n_bumps_++;
    last_ = boost::posix_time::microsec_clock::local_time();
    
    return FramesPerSeconds();
  }
  
  virtual float FramesPerMuSeconds() const {
    boost::posix_time::time_duration diff = last_ - first_;
    return float(n_bumps_) / diff.total_microseconds(); 
  }
  
  virtual float FramesPerSeconds() const {
    return FramesPerMuSeconds() * 1e6;
  }
  
  virtual float RemainingSeconds(unsigned int max) {
    unsigned int remaining = max - n_bumps_;
    return remaining / FramesPerSeconds();
  }
  
  virtual float RemainingMinutes(unsigned int max) {
    return RemainingSeconds(max) / 60.0;
  }
  
  virtual float RemainingHours(unsigned int max) {
    return RemainingMinutes(max) / 60.0;
  }
  
private:  
  unsigned int n_bumps_;
  boost::posix_time::ptime first_;
  boost::posix_time::ptime last_;
};


} //ns timer
} //ns rv

#endif