#ifndef RV_IO_LS_H
#define RV_IO_LS_H

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace rv {
namespace io {

inline void ListFiles(boost::filesystem::path dir, std::vector<boost::filesystem::path>& files) {
  for(boost::filesystem::directory_iterator end, current(dir); current != end; ++current) {
    boost::filesystem::path cp = current->path();
    files.push_back(cp);
  }
}


inline void ListFiles(boost::filesystem::path dir, std::string regex, std::vector<boost::filesystem::path>& files) {
  boost::regex expression(regex);
  for(boost::filesystem::directory_iterator end, current(dir); current != end; ++current) {
    boost::filesystem::path cp = current->path();

    boost::cmatch what;
    std::string cpStr = cp.filename().string();
    if(boost::regex_match(cpStr.c_str(), what, expression)) {
      files.push_back(cp);
    }
  }
}


inline void ListDirectories(boost::filesystem::path dir, std::vector<boost::filesystem::path>& dirs) {
  for(boost::filesystem::directory_iterator end, current(dir); current != end; ++current) {
    boost::filesystem::path cp = current->path();
    if(is_directory(cp)) {
      dirs.push_back(cp);
    }
  }
}


inline void ListFilesRecursive(boost::filesystem::path dir, std::vector<boost::filesystem::path>& files) {
  for(boost::filesystem::recursive_directory_iterator end, current(dir); current != end; ++current) {
    boost::filesystem::path cp = current->path();
    files.push_back(cp);
  }
}

inline void ListFilesRecursive(boost::filesystem::path dir, std::string regex, std::vector<boost::filesystem::path>& files) {
  boost::regex expression(regex);
  for(boost::filesystem::recursive_directory_iterator end, current(dir); current != end; ++current) {
    boost::filesystem::path cp = current->path();

    boost::cmatch what;
    std::string cpStr = cp.filename().string();
    if(boost::regex_match(cpStr.c_str(), what, expression)) {
      files.push_back(cp);
    }
  }
}

  
} //ns ls
} //ns rv

#endif
