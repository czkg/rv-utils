#ifndef RV_LOG_LOG_H
#define RV_LOG_LOG_H

#include <iostream>
#include <sstream>

#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>


namespace rv {
namespace log {


enum LogLevel {
  INFO = 0,
  WARNING = 1,
  ERROR = 2,
  FATAL_ERROR = 3
};


class LogMessage {
public:
  LogMessage(LogLevel log_level) : log_level_(log_level) {}
  
  virtual ~LogMessage() {
    std::string type = "";
    if(log_level_ == INFO) {
      type = "[INFO]";
    }
    else if(log_level_ == WARNING) {
      type = "[WARNING]";
    }
    else if(log_level_ == ERROR) {
      type = "[ERROR]";
    }
    else if(log_level_ == FATAL_ERROR) {
      type = "[FATAL_ERROR]";
    }
    
    #pragma omp critical (RV_LOG_LOGMESSAGE_DESTRUCTOR)
    {
      std::cout << type << message_.str() << std::endl;
    }
    
    if(log_level_ == ERROR || log_level_ == FATAL_ERROR) {
      exit(-1);
    }
  }
  
  template <typename T>
  LogMessage& operator<<(const T& obj) {
    message_ << obj;
    return *this;
  }
  
private:
  LogLevel log_level_;
  std::stringstream message_;
};


class LogMessageContainer {
public:
  LogMessageContainer(LogLevel log_level) {
    log_message_ = boost::make_shared<LogMessage>(log_level);
  }
  
  //copy constructor
  LogMessageContainer(const LogMessageContainer& obj) {
    log_message_ = obj.log_message_;
  }
  
  virtual ~LogMessageContainer() {}
  
  
  template <typename T>
  LogMessage& operator<<(const T& obj) {
    return log_message_->operator<<(obj);
  }
  
private:
  boost::shared_ptr<LogMessage> log_message_;
};



class Log {
public:
  virtual ~Log() {}
  
  static Log& i() {
    boost::shared_ptr<Log> i;
    #pragma omp critical (RV_LOG_LOG)
    {
      static boost::shared_ptr<Log> instance(new Log());
      i = instance;
    }
    return *i;
  }
  
  virtual LogMessageContainer operator()(LogLevel log_level) {
    return LogMessageContainer(log_level);
  }
  
private:
  Log() {}
  
};


} //ns log
} //ns rv



#ifndef LOG_INFO
  #define LOG_INFO rv::log::Log::i()(rv::log::INFO) << "[" << boost::filesystem::path(__FILE__).filename().c_str() << ":" << __LINE__ << "] "
#endif

#ifndef LOG_WARNING
  #define LOG_WARNING rv::log::Log::i()(rv::log::WARNING) << "[" << boost::filesystem::path(__FILE__).filename().c_str() << ":" << __LINE__ << "] "
#endif

#ifndef LOG_ERROR
  #define LOG_ERROR rv::log::Log::i()(rv::log::ERROR) << "[" << boost::filesystem::path(__FILE__).filename().c_str() << ":" << __LINE__ << "] "
#endif

#ifndef LOG_FATAL_ERROR
  #define LOG_FATAL_ERROR rv::log::Log::i()(rv::log::FATAL_ERROR) << "[" << boost::filesystem::path(__FILE__).filename().c_str() << ":" << __LINE__ << "] "
#endif


#endif