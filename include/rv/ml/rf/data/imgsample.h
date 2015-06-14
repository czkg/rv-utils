#ifndef RV_RF_IMG_SAMPLE_H
#define RV_RF_IMG_SAMPLE_H

#include <vector>

#include <opencv2/core/core.hpp>

#include <boost/shared_ptr.hpp>

#include <rv/log/log.h>

#include <rv/ml/rf/data/sample.h>


namespace rv {
namespace rf {
    
class ImgSample : public Sample {        
public:
  ImgSample() {}

  ImgSample(cv::Mat_<float> img, int cx, int cy) : 
          cx_(cx), cy_(cy) { 
      imgs_.push_back(img);
  }

  ImgSample(std::vector<cv::Mat_<float> > imgs, int cx, int cy) : 
      imgs_(imgs), cx_(cx), cy_(cy)
  { }
  
  virtual ~ImgSample() {}
  
  virtual float operator()(int c, int h, int w) const;
  
  virtual int channels() const { return imgs_.size(); }
  virtual int height() const { return imgs_[0].rows; }
  virtual int width() const { return imgs_[0].cols; }
    
protected:        
  std::vector<cv::Mat_<float> > imgs_;
  int cx_;
  int cy_;
};



class ImgReplicateBorderSample : public ImgSample {  
public:
  ImgReplicateBorderSample() {}
  ImgReplicateBorderSample(cv::Mat_<float> img, int cx, int cy) : ImgSample(img, cx, cy) {}
  ImgReplicateBorderSample(std::vector<cv::Mat_<float> > imgs, int cx, int cy) : ImgSample(imgs, cx, cy) {}
  
  virtual float operator()(int c, int h, int w) const;
};
    
}
}


#endif