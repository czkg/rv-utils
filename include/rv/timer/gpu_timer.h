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
