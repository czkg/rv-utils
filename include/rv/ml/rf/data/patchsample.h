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
