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

#ifndef RV_CAMERA_CAMERA_HPP
#define RV_CAMERA_CAMERA_HPP

#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>

#include <opencv2/core/core.hpp>

#include <set>

#include "camera_image.h"
#include "camera_listener.h"

#include <rv/log/log.h>

namespace rv {
namespace camera {

    
class Camera {
public:        
  Camera() {}
  virtual ~Camera() {}
  
  virtual bool start() {
    if(registered_types_.size() == 0) {
      LOG_WARNING << "starting camera with no types defined";
    }
    
    return startInternals();
  }
  
  virtual bool stop() = 0;

  virtual void registerType(const std::string& type) {
    registered_types_.insert(type);
  }

  virtual void registerAllTypes() {
    std::set<std::string> im_types = types();
    for(std::set<std::string>::iterator it = im_types.begin(); it != im_types.end(); ++it) {
      registered_types_.insert(*it);
    }
  }

  virtual void unregisterType(const std::string& type) {
    registered_types_.erase(type);
  }

  virtual void unregisterAllTypes() {
    registered_types_.clear();
  }

  virtual bool isRegisteredType(const std::string& type) {
    return registered_types_.find(type) != registered_types_.end();
  }

  
  virtual bool read(const std::string& type, CameraImage& im) {
    std::set<std::string> im_types = types();
    if(im_types.find(type) != im_types.end()) {
      im.ts_ = ims_[type].ts_;
      im.im_ = ims_[type].im_.clone();
      
      return !im.ts_.is_special();
    }
    
    return false;
  }
  
  virtual bool readLocked(const std::string& type, CameraImage& im) {
    mtx_.lock();
    bool valid = read(type, im);
    mtx_.unlock();
    
    return valid;
  }
  
  virtual void readAll(std::map<std::string, CameraImage >& ims) {
    std::set<std::string> im_types = types();
    for(std::set<std::string>::iterator it = im_types.begin(); it != im_types.end(); ++it) {
      std::string type = *it;
      readLocked(type, ims[type]);
    }
  }
  
  virtual void readAllLocked(std::map<std::string, CameraImage>& ims) {
    std::set<std::string> im_types = types();
    
    mtx_.lock();
    for(std::set<std::string>::iterator it = im_types.begin(); it != im_types.end(); ++it) {
      std::string type = *it;
      read(type, ims[type]);
    }
    
    mtx_.unlock();
  }
  
  
  virtual std::set<std::string> types() {
    static std::set<std::string> types_;
    return types_;
  }
  
  
  virtual bool config(const std::string& param, int value) {
    return false;
  }
  virtual bool config(const std::string& param, double value) {
    return false;
  }
  
  
  virtual void addListener(boost::shared_ptr<CameraListener> listener) {
    listeners_.push_back(listener);
  }
    
        
protected:
  virtual bool startInternals() = 0;

  virtual void update(const std::string& type, boost::posix_time::ptime ts, cv::Mat im, bool clone, bool flip) {
    mtx_.lock();
    
    cv::Mat im_set;
    if(clone) {
        im_set = im.clone();
    }
    else {
        im_set = im;
    }
    
    if(flip) {
        cv::flip(im_set, im_set, 1);
    }
    
    ims_[type].im_ = im_set;
    ims_[type].ts_ = ts;
    fireCameraImageChanged(type);
    
    mtx_.unlock();
  }
    
private:
  void fireCameraImageChanged(const std::string& type) {
    for(size_t idx = 0; idx < listeners_.size(); ++idx) {
      cv::Mat im_data_clone = ims_[type].im_.clone();
      CameraImage ci_clone(ims_[type].ts_, im_data_clone);
      
      listeners_[idx]->onNewCameraImage(type, ci_clone);
    }
  }
  
  Camera(const Camera&) {}
  Camera& operator=(const Camera&);
    
    
private:
  std::map<std::string, CameraImage> ims_;
  boost::mutex mtx_;
  
  std::vector<boost::shared_ptr<CameraListener> > listeners_;

  std::set<std::string> registered_types_;
};

    

    
}   
}


#endif
