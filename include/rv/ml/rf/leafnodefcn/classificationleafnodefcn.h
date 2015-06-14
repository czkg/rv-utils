#ifndef RF_CLASSIFICATIONLEAFNODEFCN_H
#define RF_CLASSIFICATIONLEAFNODEFCN_H

#include <vector>
#include <iostream>

#include <boost/shared_ptr.hpp>

#include <opencv2/core/core.hpp>

#include <rv/ml/rf/leafnodefcn/leafnodefcn.h>

namespace rv {
namespace rf {
    
class ClassificationLeafNodeFcn : public LeafNodeFcn {        
public:
  ClassificationLeafNodeFcn() {}
  virtual ~ClassificationLeafNodeFcn() {}
  
  virtual boost::shared_ptr<LeafNodeFcn> Copy() const {
    boost::shared_ptr<ClassificationLeafNodeFcn> fcn = boost::make_shared<ClassificationLeafNodeFcn>();
    fcn->stat_.resize(stat_.size());
    for(size_t stat_idx = 0; stat_idx < stat_.size(); ++stat_idx) {
      fcn->stat_[stat_idx] = CopyRfMat(stat_[stat_idx]);
    }
    
    return fcn;
  }
  
  virtual boost::shared_ptr<LeafNodeFcn> Create(
      const LeafNodeFcnParameter& param,
      const std::vector<SamplePtr>& samples, 
      const VecTargetPtr& targets) const;

  virtual VecTargetPtr Eval(const SamplePtr sample,
      const std::vector<boost::shared_ptr<LeafNodeFcn> >& fcns) const;

  
  virtual LeafNodeFcnParameter::LeafNodeFcnType type() const { return LeafNodeFcnParameter::CLASSIFICATION; }
  
DISABLE_COPY_AND_ASSIGN(ClassificationLeafNodeFcn);
};


}
}

#endif
