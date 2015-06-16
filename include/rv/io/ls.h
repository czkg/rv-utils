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
