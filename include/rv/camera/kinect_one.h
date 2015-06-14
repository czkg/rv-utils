#ifndef RV_CAMERA_CREATIVE_HPP
#define RV_CAMERA_CREATIVE_HPP

#include "camera.hpp"

#include <Kinect.h>

namespace rv {
namespace camera {

class KinectOneCamera : public Camera {
public:    
    KinectOneCamera() {
        color_rgba_ = new RGBQUAD[1080 * 1920];
    }

    virtual ~KinectOneCamera() {
        delete[] color_rgba_;
    }
    
    virtual bool start() {   
        kinect_sensor_ = 0;  
        color_reader_ = 0;  
        infrared_reader_ = 0;  
        depth_reader_ = 0;

        //open kinect and readers
        HRESULT hr = GetDefaultKinectSensor(&kinect_sensor_);
        if(FAILED(hr)) {
            std::cout << "Kinect One: GetDefaultKinectSensor failed" << std::endl;
            return false;
        }

        hr = kinect_sensor_->Open();
        if(FAILED(hr)) {
            std::cout << "Kinect One: kinect_sensor_->Open() failed" << std::endl;
            return false;
        }
        
        //color
        if(isRegisteredType(typeRgb())) {
            IColorFrameSource* pColorFrameSource = NULL;
            hr = kinect_sensor_->get_ColorFrameSource(&pColorFrameSource);
            if(FAILED(hr)) {
                std::cout << "Kinect One: get_ColorFrameSource failed" << std::endl;
                return false;
            }

            hr = pColorFrameSource->OpenReader(&color_reader_);
            if(FAILED(hr)) {
                std::cout << "Kinect One: open color_reader_ failed" << std::endl;
                return false;
            }

            if(pColorFrameSource != NULL) pColorFrameSource->Release();
        }

        //depth
        if(isRegisteredType(typeDepth())) {
            IDepthFrameSource* pDepthFrameSource = NULL;
            hr = kinect_sensor_->get_DepthFrameSource(&pDepthFrameSource);
            if(FAILED(hr)) {
                std::cout << "Kinect One: get_DepthFrameSource failed" << std::endl;
                return false;
            }

            hr = pDepthFrameSource->OpenReader(&depth_reader_);
            if(FAILED(hr)) {
                std::cout << "Kinect One: open depth_reader_ failed" << std::endl;
                return false;
            }

            if(pDepthFrameSource != NULL) pDepthFrameSource->Release();
        }

        //ir
        if(isRegisteredType(typeIr())) {
            IInfraredFrameSource* pInfraredFrameSource = NULL;
            hr = kinect_sensor_->get_InfraredFrameSource(&pInfraredFrameSource);
            if(FAILED(hr)) {
                std::cout << "Kinect One: get_InfraredFrameSource failed" << std::endl;
                return false;
            }

            hr = pInfraredFrameSource->OpenReader(&infrared_reader_);
            if(FAILED(hr)) {
                std::cout << "Kinect One: open infrared_reader_ failed" << std::endl;
                return false;
            }
        
            if(pInfraredFrameSource != NULL) pInfraredFrameSource->Release();
        }

        //start thread
        run_ = true;
        startCamera();

        return true;
    }
    
    virtual bool stop() {
        run_ = false;
        thread_.join();
        
        if(color_reader_ != NULL) color_reader_->Release();
        if(depth_reader_ != NULL) depth_reader_->Release();
        if(infrared_reader_ != NULL) infrared_reader_->Release();

        kinect_sensor_->Close();
        if(kinect_sensor_ != NULL) kinect_sensor_->Release();

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
    virtual void startCamera() {
        thread_ = boost::thread(&KinectOneCamera::process, this);
    }

    virtual bool readDepth(CameraImage& im) {
        if(depth_reader_ == 0) {
            std::cout << "Kinect One: depth reader == 0" << std::endl;
        }

        IDepthFrame* depth_frame = NULL;
        HRESULT hr = depth_reader_->AcquireLatestFrame(&depth_frame);
        boost::posix_time::ptime ts = boost::posix_time::microsec_clock::universal_time();
        if(FAILED(hr)) {
            return false;
        }

        if(im.ts_.is_special()) {
            IFrameDescription* frame_description = NULL;
            hr = depth_frame->get_FrameDescription(&frame_description);
            if(FAILED(hr)) return false;
        
            int height, width;

            hr = frame_description->get_Height(&height);
            if(FAILED(hr)) return false;

            hr = frame_description->get_Width(&width);
            if(FAILED(hr)) return false;

            if(frame_description != NULL) frame_description->Release();

            im.im_ = cv::Mat_<float>(height, width);
        }

        UINT16* buffer; 
        UINT buffersize;
        hr = depth_frame->AccessUnderlyingBuffer(&buffersize, &buffer);  
        if(FAILED(hr)) {
            return false;
        }

        im.ts_ = ts;

        int buffer_idx = 0;
        for(cv::MatIterator_<float> it = im.im_.begin<float>(); it != im.im_.end<float>(); ++it, ++buffer_idx) {
            *it = buffer[buffer_idx];
        }
        
        if(depth_frame != NULL) {
            depth_frame->Release();
        }

        return true;
    }

    virtual bool readIr(CameraImage& im) {
        if(infrared_reader_ == 0) {
            std::cout << "Kinect One: infrared reader == 0" << std::endl;
        }

        IInfraredFrame* ir_frame = NULL;
        HRESULT hr = infrared_reader_->AcquireLatestFrame(&ir_frame);
        boost::posix_time::ptime ts = boost::posix_time::microsec_clock::universal_time();
        if(FAILED(hr)) {
            return false;
        }

        if(im.ts_.is_special()) {
            IFrameDescription* frame_description = NULL;
            hr = ir_frame->get_FrameDescription(&frame_description);
            if(FAILED(hr)) return false;
        
            int height, width;

            hr = frame_description->get_Height(&height);
            if(FAILED(hr)) return false;

            hr = frame_description->get_Width(&width);
            if(FAILED(hr)) return false;

            if(frame_description != NULL) frame_description->Release();

            im.im_ = cv::Mat_<float>(height, width);
        }

        UINT16* buffer; 
        UINT buffersize;
        hr = ir_frame->AccessUnderlyingBuffer(&buffersize, &buffer);  
        if(FAILED(hr)) {
            return false;
        }

        im.ts_ = ts;

        int buffer_idx = 0;
        for(cv::MatIterator_<float> it = im.im_.begin<float>(); it != im.im_.end<float>(); ++it, ++buffer_idx) {
            *it = buffer[buffer_idx] / 1000.0;
        }
        
        if(ir_frame != NULL) {
            ir_frame->Release();
        }

        return true;
    }

    virtual bool readColor(CameraImage& im) {
        if(color_reader_ == 0) {
            std::cout << "Kinect One: color reader == 0" << std::endl;
        }

        IColorFrame* color_frame = NULL;
        HRESULT hr = color_reader_->AcquireLatestFrame(&color_frame);
        boost::posix_time::ptime ts = boost::posix_time::microsec_clock::universal_time();
        if(FAILED(hr)) {
            return false;
        }

        if(im.ts_.is_special()) {
            IFrameDescription* frame_description = NULL;
            hr = color_frame->get_FrameDescription(&frame_description);
            if(FAILED(hr)) return false;
        
            int height, width;

            hr = frame_description->get_Height(&height);
            if(FAILED(hr)) return false;

            hr = frame_description->get_Width(&width);
            if(FAILED(hr)) return false;

            if(frame_description != NULL) frame_description->Release();

            im.im_ = cv::Mat_<cv::Vec3b>(height, width);
        }

        ColorImageFormat imageFormat = ColorImageFormat_None;
        hr = color_frame->get_RawColorImageFormat(&imageFormat);
        if(FAILED(hr)) return false;

        
        UINT nBufferSize = 0;
        RGBQUAD *buffer = NULL;
        if (imageFormat == ColorImageFormat_Bgra) {
            hr = color_frame->AccessRawUnderlyingBuffer(&nBufferSize, reinterpret_cast<BYTE**>(&buffer));
            if(FAILED(hr)) return false;
        }
        else if (color_rgba_) {
            buffer = color_rgba_;
            nBufferSize = 1080 * 1920 * sizeof(RGBQUAD);
            hr = color_frame->CopyConvertedFrameDataToArray(nBufferSize, reinterpret_cast<BYTE*>(buffer), ColorImageFormat_Bgra);            
        }
        else {
            return false;
        }

        im.ts_ = ts;

        int buffer_idx = 0;
        for(cv::MatIterator_<cv::Vec3b> it = im.im_.begin<cv::Vec3b>(); it != im.im_.end<cv::Vec3b>(); ++it, ++buffer_idx) {
            (*it)[0] = buffer[buffer_idx].rgbBlue;
            (*it)[1] = buffer[buffer_idx].rgbGreen;
            (*it)[2] = buffer[buffer_idx].rgbRed;
        }
        
        if(color_frame != NULL) color_frame->Release();

        return true;
    }

    virtual void process() {      
        CameraImage im_depth;  
        CameraImage im_ir;  
        CameraImage im_rgb;

        while(run_) {
            if(isRegisteredType(typeDepth()) && readDepth(im_depth)) {
                update(typeDepth(), im_depth.ts_, im_depth.im_, true, true);
            }

            if(isRegisteredType(typeIr()) && readIr(im_ir)) {
                update(typeIr(), im_ir.ts_, im_ir.im_, true, true);
            }

            if(isRegisteredType(typeRgb()) && readColor(im_rgb)) {
                update(typeRgb(), im_rgb.ts_, im_rgb.im_, true, true);
            }
        }
    }
    
    KinectOneCamera(const KinectOneCamera&) {}
    
private:
    boost::thread thread_;
    bool run_;

    IKinectSensor* kinect_sensor_;
    IColorFrameReader* color_reader_;
    IInfraredFrameReader* infrared_reader_;
    IDepthFrameReader* depth_reader_;

    RGBQUAD* color_rgba_;
};


}
}

#endif