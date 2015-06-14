#ifndef RV_RF_PATCH_SAMPLE_H
#define RV_RF_PATCH_SAMPLE_H

#include <vector>

#include <opencv2/core/core.hpp>

#include <boost/shared_ptr.hpp>

#include <rv/log/log.h>

#include <rv/ml/rf/data/sample.h>


namespace rv {
namespace rf {
    
class PatchSample : public Sample {    
protected:    
    std::vector<cv::Mat_<float> > patches_;
    
public:
    PatchSample() {}

    PatchSample(cv::Mat_<float> patch) { 
        patches_.push_back(patch);
    }

    PatchSample(std::vector<cv::Mat_<float> > patches) : 
        patches_(patches)
    { }
    
    virtual ~PatchSample() {}
    
    
    virtual float operator()(int c, int h, int w) const;
    
    virtual int channels() const { return patches_.size(); }
    virtual int height() const { return patches_[0].rows; }
    virtual int width() const { return patches_[0].cols; }
};
    
}
}


#endif
