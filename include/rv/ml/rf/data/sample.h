#ifndef RF_SAMPLE_H
#define RF_SAMPLE_H

#include <vector>

#include <opencv2/core/core.hpp>

#include <boost/shared_ptr.hpp>


namespace rv {
namespace rf {
    
class Sample {        
public:
    Sample() {}
    
    virtual ~Sample() {}
    
    virtual float operator()(int c, int h, int w) const = 0;
    virtual float at(int c, int h, int w) const {
      return operator()(c, h, w);
    }

    virtual int channels() const = 0;
    virtual int height() const = 0;
    virtual int width() const = 0;

    virtual int dim() const { return channels() * height() * width(); }
};
    
typedef boost::shared_ptr<Sample> SamplePtr;
    
}
}


#endif
