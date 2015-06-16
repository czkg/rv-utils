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
