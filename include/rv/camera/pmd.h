#ifndef RV_CAMERA_PMD_HPP
#define RV_CAMERA_PMD_HPP

#include "camera.h"

#include <pmdsdk2.h>


namespace rv {
namespace camera {

class PmdCamera : public Camera {
public:    
  PmdCamera() {}
  virtual ~PmdCamera() {}
  
     
  virtual bool stop() {
    //stop thread
    run_ = false;
    thread_.join();
    
    //close camera connection
    int pmd_status = pmdClose(cam_);
    if (pmd_status != PMD_OK) {
      char err[128];
      std::cout << "PMD Error 5: could not close camera correctly." << std::endl;
      return false;
    }
    
    cam_ = 0;
    
    return true;
  }
  
  virtual std::set<std::string> types() {
    static std::set<std::string> types_;
    if(types_.size() == 0) {
      types_.insert(typeDepth());
      types_.insert(typeIr());
      types_.insert(typePhase0());
      types_.insert(typePhase1());
      types_.insert(typePhase2());
      types_.insert(typePhase3());
    }
    return types_;
  }
  
  static const std::string typeDepth() { return "depth"; }
  static const std::string typeIr() { return "ir"; }
  static const std::string typePhase0() { return "phase0"; }
  static const std::string typePhase1() { return "phase1"; }
  static const std::string typePhase2() { return "phase2"; }
  static const std::string typePhase3() { return "phase3"; }
  
  
  virtual bool config(const std::string& param, int value) {
    return Camera::config(param, value);
  }
  
  virtual bool config(const std::string& param, double value) {
    return Camera::config(param, value);
  }
    
    
protected:    
  virtual bool startInternals() {                
    //open camera connection
    int pmd_status = pmdOpen(&cam_, srcPlugin().c_str(), srcCalib().c_str(), procPlugin().c_str(), procCalib().c_str());
    if(pmd_status != PMD_OK){
      char err[128];
      pmdGetLastError(0, err, 128);
      std::cout << "PMD Error 1: " << err << std::endl;
      return false;
    }
    
    pmd_status = pmdUpdate (cam_);
    if (pmd_status != PMD_OK) {
      pmdClose (cam_);
      char err[128];
      pmdGetLastError(0, err, 128);
      std::cout << "PMD Error 2: " << err << std::endl;
      return false;
    }
    
    pmd_status = pmdGetSourceDataDescription (cam_, &dd_);
    if (pmd_status != PMD_OK) {
      pmdClose (cam_);
      char err[128];
      pmdGetLastError(0, err, 128);
      std::cout << "PMD Error 3: " << err << std::endl;
      return false;
    }
    
    if (dd_.subHeaderType != PMD_IMAGE_DATA) {
      pmdClose (cam_);
      char err[128];
      pmdGetLastError(0, err, 128);
      std::cout << "PMD Error 4: Source data is not an image." << std::endl;
      return false;
    } 
    else {
      std::cout << "PMD size: " << dd_.img.numRows << " x " << dd_.img.numColumns << std::endl;
    }
    
    pmdProcessingCommand(cam_, 0, 0, "SetBilateralFilter off");
            
    char loaded[8];
    pmdSourceCommand(cam_, loaded, 8, "IsCalibrationDataLoaded");
    
    if(strcmp(loaded, "Yes") == 0) {
      std::cout << "PMD: calibration file loaded." << std::endl;
    }
    else {
      std::cout << "PMD Warning: NO calibration file loaded." << std::endl;
    }
    
    char lens[128];
    pmd_status = pmdSourceCommand(cam_, lens, 128, "GetLensParameters");
    if(pmd_status == PMD_OK) {
      std::cout << "PMD lens parameters: " << lens << std::endl;
    }
    
    //start thread
    run_ = true;
    startProcess();
    
    return true;
  }
  
  
  virtual void process() {        
    int height = yEnd() - yStart();
    int width = xEnd() - xStart();
    cv::Rect roi(xStart(), yStart(), width, height);
    
    cv::Mat_<float> depth = cv::Mat_<float>(dd_.img.numRows, dd_.img.numColumns);
    cv::Mat_<float> ir = cv::Mat_<float>(dd_.img.numRows, dd_.img.numColumns);
    
    std::cout << depth.rows << " x " << depth.cols << " | run = " << run_ << std::endl;
    
    while(run_) {
      //Update
      int pmd_status = pmdUpdate (cam_);
      if (pmd_status != PMD_OK) {
        char err[128];
        pmdGetLastError (cam_, err, 128);
        std::cout << "PMD error 6: " << err << std::endl;
        
        run_ = false;
        pmdClose (cam_);
      }
        
      boost::posix_time::ptime ts = boost::posix_time::microsec_clock::universal_time();
      
      
      //Grab depth
      if(isRegisteredType(typeDepth())) {
        pmd_status = pmdGetDistances(cam_, (float*) depth.data, dd_.img.numColumns * dd_.img.numRows * sizeof (float));
        if (pmd_status != PMD_OK) {
          char err[128];
          pmdGetLastError (cam_, err, 128);
          std::cout << "PMD error: " << err << std::endl;
      
          run_ = false;
          pmdClose (cam_);
        }
        depth = depth * 1e3;
        update(typeDepth(), ts, depth(roi), true, false);
      }
        
        
      //Grab ir
      if(isRegisteredType(typeIr())) {
        pmd_status = pmdGetAmplitudes(cam_, (float*) ir.data, dd_.img.numColumns * dd_.img.numRows * sizeof (float));
        if (pmd_status != PMD_OK) {
          char err[128];
          pmdGetLastError (cam_, err, 128);
          std::cout << "PMD error 7: " << err << std::endl;
      
          run_ = false;
          pmdClose (cam_);
        }
        update(typeIr(), ts, ir(roi), true, false);
      }
    }
  }
  
  //-----------------------------------------------------------------
  //Functions to overload in Pmd camera classes
  virtual void startProcess() {
    thread_ = boost::thread(&PmdCamera::process, this);
  }
  
  virtual size_t xStart() const { return 0; };
  virtual size_t xEnd() const { return 165; };
  virtual size_t yStart() const { return 0; };
  virtual size_t yEnd() const { return 120; };
  
  virtual std::string srcPlugin() const { return "don not use base class"; }
  virtual std::string srcCalib() const { return "don not use base class"; }
  virtual std::string procPlugin() const { return "don not use base class"; }
  virtual std::string procCalib() const { return "don not use base class"; }
  
    
protected:
  bool run_; 
  boost::thread thread_;
  
  PMDHandle cam_;
  PMDHandle hndProc_;
  PMDDataDescription dd_;
    
};


//------------------------------------------------------------------------------
class PmdNanoCamera : public PmdCamera {
public:
  PmdNanoCamera() {}
  virtual ~PmdNanoCamera() {}
  
protected:
  
  virtual void startProcess() {
    PmdCamera::thread_ = boost::thread(&PmdNanoCamera::process, this);
  }
  
  virtual size_t xStart() const { return 0; };
  virtual size_t xEnd() const { return 165; };
  virtual size_t yStart() const { return 0; };
  virtual size_t yEnd() const { return 120; };
  
#if defined _WIN64
  virtual std::string srcPlugin() const { return "camboardnano.W64.pap"; }
  virtual std::string srcCalib() const { return ""; }
  virtual std::string procPlugin() const { return "camboardnanoproc.W64.ppp"; }
  virtual std::string procCalib() const { return ""; }
#elif defined _WIN32
  virtual std::string srcPlugin() const { return "camboardnano.W32.pap"; }
  virtual std::string srcCalib() const { return ""; }
  virtual std::string procPlugin() const { return "camboardnanoproc.W32.ppp"; }
  virtual std::string procCalib() const { return ""; }
#else
  virtual std::string srcPlugin() const { return "camboardnano"; }
  virtual std::string srcCalib() const { return ""; }
  virtual std::string procPlugin() const { return "camboardnanoproc"; }
  virtual std::string procCalib() const { return ""; }
#endif

};



//------------------------------------------------------------------------------
class PmdPicoCamera : public PmdCamera {
public:
  PmdPicoCamera() {}
  virtual ~PmdPicoCamera() {}
    
protected:
    
  virtual void startProcess() {
    PmdCamera::thread_ = boost::thread(&PmdPicoCamera::process, this);
  }
  
  virtual size_t xStart() const { return 0; };
  virtual size_t xEnd() const { return 176; };
  virtual size_t yStart() const { return 0; };
  virtual size_t yEnd() const { return 120; };
  
#if defined _WIN64
  virtual std::string srcPlugin() const { return "./camboardpico.W64.pap"; }
  virtual std::string srcCalib() const { return ""; }
  virtual std::string procPlugin() const { return "./camboardpicoproc.W64.ppp"; }
  virtual std::string procCalib() const { return ""; }
#elif defined _WIN32
  virtual std::string srcPlugin() const { return "./camboardpico.W32.pap"; }
  virtual std::string srcCalib() const { return ""; }
  virtual std::string procPlugin() const { return "./camboardpicoproc.W32.ppp"; }
  virtual std::string procCalib() const { return ""; }
#else
  virtual std::string srcPlugin() const { return "./camboardpico"; }
  virtual std::string srcCalib() const { return ""; }
  virtual std::string procPlugin() const { return "./camboardpicoproc"; }
  virtual std::string procCalib() const { return ""; }
#endif

};


}
}


#endif
