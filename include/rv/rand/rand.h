#ifndef RV_RAND_RAND_H
#define RV_RAND_RAND_H

#include <time.h>

#include <opencv2/core/core.hpp>

#include <boost/make_shared.hpp>

namespace rv {
namespace rand {


template <typename Dtype>
class Rand {
public:
  virtual ~Rand() {}
  
  static Rand& i() {
    boost::shared_ptr<Rand> i;
    #pragma omp critical (RV_RAND_RAND)
    {
      static boost::shared_ptr<Rand> instance(new Rand());
      i = instance;
    }
    return *i;
  }
  
  static Dtype Gaussian(Dtype mu, Dtype sigma) {
    return i().GaussianPrivate(mu, sigma);
  }
  
  static Dtype Uniform(Dtype from, Dtype to) {
    return i().UniformPrivate(from, to);
  }
  
private:
  Rand() : rng_(time(0)) {}
  
  Dtype GaussianPrivate(Dtype mu, Dtype sigma) {
    Dtype val = 0;
    #pragma omp critical (RV_RAND_RAND)
    {
      val = rng_.gaussian(sigma) + mu;
    }
    return val;
  }
  
  Dtype UniformPrivate(Dtype from, Dtype to) {
    Dtype val = 0;
    #pragma omp critical (RV_RAND_RAND)
    {
      val = rng_.uniform(from, to);
    }
    return val;
  }
  
private:
  cv::RNG rng_;
};
  
  
template <typename T>
inline void Permute( std::vector<T>& vec ) {
  for(size_t i = 0; i < vec.size(); ++i) {
    size_t j = Rand<int>::Uniform(0, vec.size());
    T tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
  }
}

inline std::vector<int> PermuteIndices(size_t n) {
  std::vector<int> indices(n);
  
  for(size_t i = 0; i < n; ++i) {
    indices[i] = i;
  }
  
  Rand<int>& rand = Rand<int>::i();
  for(size_t i = 0; i < indices.size(); ++i) {
    size_t j = Rand<int>::Uniform(0, indices.size());
    int tmp = indices[i];
    indices[i] = indices[j];
    indices[j] = tmp;
  }
  
  return indices;
}

template <typename T>
inline std::vector<T> ApplyPermutation(const std::vector< T >& vec, const std::vector< int >& indices) {
  std::vector<T> shuffled(vec.size());
  
  for(size_t i = 0; i < indices.size(); ++i) {
    shuffled[i] = vec[indices[i]];
  }
  
  return shuffled;
}


} //ns rand
} //ns rv

#endif 
