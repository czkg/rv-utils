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

#ifndef RF_LEAFNODEFCN_H
#define RF_LEAFNODEFCN_H

#include <vector>

#include <boost/make_shared.hpp>

#include <rv/io/serialization/serialization.h>
#include <rv/ml/rf/data/sample.h>
#include <rv/ml/rf/data/target.h>
#include <rv/ml/rf/proto/rf.pb.h>

namespace rv {
namespace rf {
    
//------------------------------------------------------------------------------
class LeafNodeFcn {    
public:
  LeafNodeFcn() {}
  virtual ~LeafNodeFcn() {}
  
  virtual boost::shared_ptr<LeafNodeFcn> Copy() const = 0;
  
  virtual boost::shared_ptr<LeafNodeFcn> Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const VecTargetPtr& targets) const = 0;

  virtual VecTargetPtr Eval(const SamplePtr sample,
      const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const = 0;

  virtual LeafNodeFcnParameter::LeafNodeFcnType type() const = 0;
  
  
  virtual void Save(rv::io::SerializationOut& ar) const {
    size_t n_stats = stat_.size();
    ar << n_stats;

    for(size_t stat_idx = 0; stat_idx < stat_.size(); ++stat_idx) {
      RfMatPtr mat = stat_[stat_idx];

      int rows = mat->rows();
      int cols = mat->cols();

      ar << rows;
      ar << cols;

      for(int row = 0; row < rows; ++row) {
        for(int col = 0; col < cols; ++col) {
          float val = (*mat)(row, col);
          ar << val;
        }
      }
    }
  }
  
  virtual void Load(rv::io::SerializationIn& ar) {
    size_t n_stats;
    ar >> n_stats;

    for(size_t stat_idx = 0; stat_idx < n_stats; ++stat_idx) {
      int rows, cols;
      ar >> rows;
      ar >> cols;

      RfMatPtr mat = CreateRfMat(rows, cols);

      for(int row = 0; row < rows; ++row) {
        for(int col = 0; col < cols; ++col) {
          float val;
          ar >> val;

          (*mat)(row, col) = val;
        }
      }

      stat_.push_back(mat);
    }
  }
  
  
  RfMatPtr stat(int idx) const { return stat_[idx]; }
  size_t stat_size() const { return stat_.size(); }
  void add_stat(RfMatPtr val) { stat_.push_back(val); }
  
protected:
  std::vector<RfMatPtr> stat_;
};

typedef boost::shared_ptr<LeafNodeFcn> LeafNodeFcnPtr;

}
}

#endif
