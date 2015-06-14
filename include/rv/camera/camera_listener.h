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
