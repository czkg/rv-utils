#include <rv/ml/rf/splitevaluator/splitevaluator.h>
#include <iostream>

float rv::rf::SplitEvaluator::Eval(const std::vector<TargetPtr>& lefttargets, 
    const std::vector<TargetPtr>& righttargets) const {
  
  float purity_left = Purity(lefttargets);
  float purity_right = Purity(righttargets);
  
  float normalize_left = 1.0;
  float normalize_right = 1.0;
  
  if(normalize_) {
    unsigned int n_left = lefttargets.size();
    unsigned int n_right = righttargets.size();
    unsigned int n_total = n_left + n_right;
    
    normalize_left = float(n_left) / float(n_total);
    normalize_right = float(n_right) / float(n_total);
  }
  
  float purity =  purity_left * normalize_left + purity_right * normalize_right;
  float weighted_purity = weight_ * purity;

  // std::cout << purity_left << ", " << purity_right << ", " 
  //   << normalize_left << ", " << normalize_right << ", " 
  //   << purity_left * normalize_left << ", " << purity_right * normalize_right;

  return weighted_purity;
}
