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
