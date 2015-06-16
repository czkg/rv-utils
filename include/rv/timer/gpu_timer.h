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

#ifndef RV_TIMER_GPU_TIMER_H
#define RV_TIMER_GPU_TIMER_H

#include <rv/timer/timer.h>

#include <cuda_runtime.h>

namespace rv {
namespace timer {

class GpuTimer : public Timer {
public:
  GpuTimer() {}
  virtual ~GpuTimer() {}
  
  virtual void start() {
    cudaEventCreate(&start_);
    cudaEventCreate(&stop_);
    cudaEventRecord(start_);
  }
  
  virtual millisec_t stop() {
    cudaEventRecord(stop_);
    cudaEventSynchronize(stop_);
    
    float ms = -1;
    cudaEventElapsedTime(&ms, start_, stop_);
    stat_.add(ms);
    
    return ms;
  }
  
private:
  cudaEvent_t start_;
  cudaEvent_t stop_;
};
  

//TODO: make thread safe / omp thread safe
class GpuBatchedTimer : public BatchedTimer {
public:  
  virtual void start(const std::string& id) {
    cudaEventCreate(&(starts_[id]));
    cudaEventCreate(&(stops_[id]));
    cudaEventRecord(starts_[id]);
  }
  
  virtual millisec_t stop(const std::string& id) {
    cudaEventRecord(stops_[id]);
    cudaEventSynchronize(stops_[id]);
    
    float ms = -1;
    cudaEventElapsedTime(&ms, starts_[id], stops_[id]);
    stats_[id].add(ms);
    
    return ms;
  }
  
  static GpuBatchedTimer& i() {
    static GpuBatchedTimer instance;
    return instance;
  }
  
protected:
  GpuBatchedTimer() {}
  virtual ~GpuBatchedTimer() {}
  
private:
  std::map<std::string, cudaEvent_t> starts_;
  std::map<std::string, cudaEvent_t> stops_;
};
  

} //ns timer
} //ns rv

#endif // BATCHEDTIMER_H
