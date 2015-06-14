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
