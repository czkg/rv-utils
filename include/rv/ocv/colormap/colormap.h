#ifndef RV_OCV_COLORMAP_H
#define RV_OCV_COLORMAP_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace rv {
namespace ocv {
  
template <typename Dtype>
class ColorMap {
public:
  virtual ~ColorMap() {}
  
  virtual cv::Mat_<cv::Vec3b> Map(const cv::Mat_<Dtype>& m, bool reverse = false) const {
    float vmin = 1e9;
    float vmax = -1e9;
    for(int row = 0; row < m.rows; ++row) {
      for(int col = 0; col < m.cols; ++col) {
        float v = m(row, col);
        if(v < vmin) vmin = v;
        if(v > vmax) vmax = v;
      }
    }
    cv::Mat_<cv::Vec3b> map(m.rows, m.cols);
    int n = map_.size();
    for(int row = 0; row < m.rows; ++row) {
      for(int col = 0; col < m.cols; ++col) {
        float v = m(row, col);
        int idx = 0;
        if(vmax != vmin) {
          idx = (n - 1) * (v - vmin) / (vmax - vmin);
        }
        
        map(row, col) = reverse ? map_[map_.size() - idx - 1] : map_[idx];
      }
    }    
    
    return map;
  }
  
  virtual cv::Mat_<cv::Vec3b> Map(const cv::Mat_<Dtype>& m, Dtype vmin, Dtype vmax, bool reverse = false) const {
    cv::Mat_<Dtype> clamped(m.rows, m.cols);
    Dtype m_vmin = 1e9;
    Dtype m_vmax = -1e9;
    for(int row = 0; row < m.rows; ++row) {
      for(int col = 0; col < m.cols; ++col) {
        float v = m(row, col);
        if(v < vmin) {
          clamped(row, col) = vmin;
        }
        else if(v > vmax) {
          clamped(row, col) = vmax;
        }
        else {
          clamped(row, col) = v;
        }

        if(v < m_vmin) m_vmin = v;
        if(v > m_vmax) m_vmax = v;
      }
    }
    
    return Map(clamped, reverse);
  }
  
  virtual void ShowSample() const {
    cv::Mat_<float> sample(30, 600);
    for(int row = 0; row < sample.rows; ++row) {
      for(int col = 0; col < sample.cols; ++col) {
        sample(row, col) = col;
      }
    }
    
    cv::imshow(name(), Map(sample));
  }
  
  virtual std::string name() const = 0;
  
protected:
  ColorMap() {}
  
private:
  ColorMap(const ColorMap<Dtype>& m);
  void operator=(const ColorMap<Dtype>& m);
  
protected:
  std::vector<cv::Vec3b> map_;
};


} //ns cv
} //ns rv


#endif
