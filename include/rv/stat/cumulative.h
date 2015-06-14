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