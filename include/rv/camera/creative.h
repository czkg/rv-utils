#ifndef RV_CAMERA_CREATIVE_HPP
#define RV_CAMERA_CREATIVE_HPP

#include "camera.h"

#include <DepthSense.hxx>


namespace rv {
namespace camera {

/// Singleton because the library needs a static function to receive new data
class Creative325Camera : public Camera {
public:    
  static Creative325Camera& i() {
    static Creative325Camera instance;
    return instance;
  }
    
  template <typename NodeType>
  NodeType getFirstAvailableNode (DepthSense::Context context) {
    // obtain the list of devices attached to the host
    std::vector<DepthSense::Device> devices = context.getDevices();

    for (std::vector<DepthSense::Device>::const_iterator iter = devices.begin(); iter != devices.end(); iter++) {
      DepthSense::Device device = *iter;

      // obtain the list of nodes of the current device
      std::vector<DepthSense::Node> nodes = device.getNodes();

      for (std::vector<DepthSense::Node>::const_iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
        DepthSense::Node node = *nodeIter;

        NodeType node_type = node.as<NodeType>();
        if (node_type.isSet()) {
          return node_type;
        }
      }
    }

    // return an unset color node
    return NodeType();
  }
        
  static void onNewColorSample (DepthSense::ColorNode obj, DepthSense::ColorNode::NewSampleReceivedData data) {
    boost::posix_time::ptime ts = boost::posix_time::microsec_clock::universal_time();
    
    int32_t width, height;
    DepthSense::FrameFormat_toResolution(data.captureConfiguration.frameFormat, &width, &height);
            
    cv::Mat_<cv::Vec3b> bgr_mat(height, width);
    
    int bgr_idx = 0;
    for(int row = 0; row < bgr_mat.rows; ++row) {
      for(int col = 0; col < bgr_mat.cols; ++col) {
        for(int c = 0; c < 3 ; ++c) {
          bgr_mat(row, col)[c] = data.colorMap[bgr_idx];
          bgr_idx++;
        }
      }
    }
    
    i().update(typeRgb(), ts, bgr_mat, false, false);
  }    
    
  static void onNewDepthSample(DepthSense::DepthNode obj, DepthSense::DepthNode::NewSampleReceivedData data) {
    boost::posix_time::ptime ts = boost::posix_time::microsec_clock::universal_time();
    
    int32_t width, height;
    DepthSense::FrameFormat_toResolution(data.captureConfiguration.frameFormat, &width, &height);
    
    cv::Mat_<float> depth_mat(height, width);
    cv::Mat_<float> ir_mat(height, width);
    
    cv::Mat_<float>::iterator depth_it = depth_mat.begin();
    cv::Mat_<float>::iterator ir_it = ir_mat.begin();
    
    for(int idx = 0; idx < width * height; ++idx, ++depth_it, ++ir_it) {
      *depth_it = data.depthMapFloatingPoint[idx] * 1e3; // in mm
      *ir_it = data.confidenceMap[idx];
    }
    
    if(i().isRegisteredType(typeDepth())) {
      i().update(typeDepth(), ts, depth_mat, false, false);
    }
    if(i().isRegisteredType(typeDepth())) {
      i().update(typeIr(), ts, ir_mat, false, false);
    }
  }
    
    
  virtual bool stop() {
    context_.quit();
    thread_.join();

    return true;
  }
    
  virtual std::set<std::string> types() {
    static std::set<std::string> types_;
    if(types_.size() == 0) {
      types_.insert(typeDepth());
      types_.insert(typeIr());
      types_.insert(typeRgb());
    }
    return types_;
  }
    
  static const std::string typeDepth() { return "depth"; }
  static const std::string typeIr() { return "ir"; }
  static const std::string typeRgb() { return "rgb"; }
    
    
  virtual bool config(const std::string& param, int value) {
    return Camera::config(param, value);
  }
  
  virtual bool config(const std::string& param, double value) {
    return Camera::config(param, value);
  }
    
    
private:
  virtual bool startInternals() {                
    context_ = DepthSense::Context::create();
    
    // color node
    if(isRegisteredType(typeRgb())) {
      DepthSense::ColorNode color_node = getFirstAvailableNode<DepthSense::ColorNode>(context_);
      if (!color_node.isSet()) {
        std::cout << "Creative 325: no color node found" << std::endl;
        return false;
      }

      DepthSense::ColorNode::Configuration color_node_config = color_node.getConfiguration();
      color_node_config.framerate = 25;
      color_node_config.frameFormat = DepthSense::FRAME_FORMAT_VGA;
      color_node_config.compression = DepthSense::COMPRESSION_TYPE_MJPEG;
      color_node_config.powerLineFrequency = DepthSense::POWER_LINE_FREQUENCY_50HZ;
      color_node.setEnableColorMap(true);
      context_.requestControl(color_node, 0);
      color_node.setConfiguration(color_node_config);

      color_node.newSampleReceivedEvent().connect(Creative325Camera::onNewColorSample);
      context_.registerNode(color_node);
    }

    //depth & ir node
    if(isRegisteredType(typeDepth()) || isRegisteredType(typeIr())) {
      DepthSense::DepthNode depth_node = getFirstAvailableNode<DepthSense::DepthNode>(context_);
      if (!depth_node.isSet()) {
        std::cout << "Creative 325: no depth node found" << std::endl;
        return false;
      }

      DepthSense::DepthNode::Configuration depth_node_config = depth_node.getConfiguration();
      depth_node_config.framerate = 25;
      depth_node_config.frameFormat = DepthSense::FRAME_FORMAT_QVGA;
      depth_node_config.mode = DepthSense::DepthNode::CAMERA_MODE_CLOSE_MODE;
      depth_node_config.saturation = true;
      depth_node.setEnableDepthMapFloatingPoint(true);
      depth_node.setEnableConfidenceMap(true);
      context_.requestControl(depth_node, 0);
      depth_node.setConfidenceThreshold(5);
      depth_node.setConfiguration(depth_node_config);

      depth_node.newSampleReceivedEvent().connect(Creative325Camera::onNewDepthSample);
      context_.registerNode(depth_node);
    }
    

    //run event loop in own thread
    thread_ = boost::thread(&Creative325Camera::startCamera, this);

    return true;
  }
  
  virtual void startCamera() {
    // start streaming
    context_.startNodes();

    // start the DepthSense main event loop
    context_.run();
  }
    
    
  Creative325Camera() {}
  Creative325Camera(const Creative325Camera&) {}
  virtual ~Creative325Camera() {}
    
private:
  boost::thread thread_;
  DepthSense::Context context_;
};


}
}

#endif
