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
