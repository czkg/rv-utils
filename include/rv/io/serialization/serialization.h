#ifndef RV_IO_SERIALIZATION
#define RV_IO_SERIALIZATION


namespace rv {
namespace io {

  
class SerializationOut {
public:
  SerializationOut(const std::string& path) : path_(path) {}
  virtual ~SerializationOut() {}

  virtual SerializationOut& operator<<(const bool& v) = 0;
  virtual SerializationOut& operator<<(const char& v) = 0;
  virtual SerializationOut& operator<<(const int& v) = 0;
  virtual SerializationOut& operator<<(const unsigned int& v) = 0;
  virtual SerializationOut& operator<<(const long int& v) = 0;
  virtual SerializationOut& operator<<(const unsigned long int& v) = 0;
  virtual SerializationOut& operator<<(const long long int& v) = 0;
  virtual SerializationOut& operator<<(const unsigned long long int& v) = 0;
  virtual SerializationOut& operator<<(const float& v) = 0;
  virtual SerializationOut& operator<<(const double& v) = 0;

protected:
  const std::string& path_;
};

class SerializationIn {
public:
  SerializationIn(const std::string& path) : path_(path) {}
  virtual ~SerializationIn() {}

  virtual SerializationIn& operator>>(bool& v) = 0;
  virtual SerializationIn& operator>>(char& v) = 0;
  virtual SerializationIn& operator>>(int& v) = 0;
  virtual SerializationIn& operator>>(unsigned int& v) = 0;
  virtual SerializationIn& operator>>(long int& v) = 0;
  virtual SerializationIn& operator>>(unsigned long int& v) = 0;
  virtual SerializationIn& operator>>(long long int& v) = 0;
  virtual SerializationIn& operator>>(unsigned long long int& v) = 0;
  virtual SerializationIn& operator>>(float& v) = 0;
  virtual SerializationIn& operator>>(double& v) = 0;

protected:
  const std::string& path_;
};




} //ns io
} //ns rv

#endif //RV_IO_SERIALIZATION
