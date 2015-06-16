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

#ifndef RV_CAMERA_CAMERA_LISTENER_HPP
#define RV_CAMERA_CAMERA_LISTENER_HPP

#include <boost/date_time.hpp>

#include "camera_image.h"

namespace rv {
namespace camera {

    
//------------------------------------------------------------------------------
class CameraListener {
public:
    CameraListener() {}
    virtual ~CameraListener() {}
    
    virtual void onNewCameraImage(const std::string& type, CameraImage& im) = 0;
    
    
protected:
    virtual long timeDifferenceInMs(const boost::posix_time::ptime& p1, const boost::posix_time::ptime& p2) {
        boost::posix_time::time_duration dur = p1 - p2;
        return dur.total_milliseconds();
    }
};



//------------------------------------------------------------------------------
class TimedCameraListener : public CameraListener {
public:
    TimedCameraListener(const std::string& type, const std::vector<boost::posix_time::ptime>& requested_times, long max_diff_in_ms) :
            type_(type), requested_times_(requested_times), max_diff_in_ms_(max_diff_in_ms), current_idx_(0) {
        
        for(size_t idx = 0; idx < requested_times_.size() - 1; ++idx) {
            if(requested_times_[idx] > requested_times[idx + 1]) {
                throw std::runtime_error("requested_times should be sorted!");
            }
        }
        
        if(max_diff_in_ms_ < 0) {
            throw std::runtime_error("max_diff_in_ms should be >= 0!");
        }
        
        current_diff_in_ms_ = max_diff_in_ms + 1;
    }
        
    virtual ~TimedCameraListener() {}
    
    
    virtual void onNewCameraImage(const std::string& type, CameraImage& im) {
        if(type != type_ || current_idx_ >= requested_times_.size()) {
            return;
        }
        
        boost::posix_time::ptime new_ts = im.ts_;
        boost::posix_time::ptime req_ts = requested_times_[current_idx_];
                
            
        //go through the requested times until we are before one
        while(req_ts < new_ts) {
            long time_diff = std::abs(timeDifferenceInMs(req_ts, new_ts));
            
            if(time_diff <= max_diff_in_ms_ && time_diff < current_diff_in_ms_) {
                current_diff_in_ms_ = time_diff;
                current_best_im_.im_ = im.im_;
                current_best_im_.ts_ = im.ts_;
            }
            
            //fire event, iff current_diff_in_ms_ < max_diff_in_ms_
            if(current_diff_in_ms_ <= max_diff_in_ms_) {
                onNewTimedCameraImage(current_best_im_, current_idx_, current_diff_in_ms_);
            }
            
            current_idx_ = current_idx_ + 1;
            current_diff_in_ms_ = max_diff_in_ms_ + 1;
            
            if(current_idx_ < requested_times_.size()) {
                req_ts = requested_times_[current_idx_];
            }
            else {
                break;
            }
        }

        //find the best value before the requested time
        if(new_ts < req_ts) { 
            long time_diff = std::abs(timeDifferenceInMs(req_ts, new_ts));
            if(time_diff <= max_diff_in_ms_ && time_diff < current_diff_in_ms_) {
                current_diff_in_ms_ = time_diff;
                current_best_im_.im_ = im.im_;
                current_best_im_.ts_ = im.ts_;
            }
        }
        
    }
    
    virtual void onNewTimedCameraImage(CameraImage& im, int idx, long diff_in_ms) = 0;
    
   
protected:
    const std::string type_;
    std::vector<boost::posix_time::ptime> requested_times_;
    long max_diff_in_ms_;
    
    int current_idx_;
    long current_diff_in_ms_;
    CameraImage current_best_im_;
};


}
}


#endif
