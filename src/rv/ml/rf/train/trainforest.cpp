#include <rv/ml/rf/train/trainforest.h>

#include <omp.h>

#include <rv/timer/cpu_timer.h>


namespace rv {
namespace rf {

ForestPtr TrainForest::Train(std::vector<SamplePtr>& samples,
      std::vector<VecPtrTargetPtr>& targets, 
      std::vector<VecPtrTargetPtr>& optimize_targets,
      TrainType train_type, const boost::shared_ptr<Forest>& old_forest) {
    
  if(optimize_targets.size() != split_evaluator_.size()) {
    LOG_ERROR << "number of split evaluators " 
      << "differs number of optimization targets";
  }

  if(targets.size() != gen_leaf_node_fcns_.size()) {
    LOG_ERROR << "number of targets (" << targets.size() << ") differs "
      << "number of leaf node fcn generators (" 
      << gen_leaf_node_fcns_.size() << ")";
  }

  if(verbose_){
    std::cout << "[TRAIN] training forest " << std::endl;

    std::cout << "[TRAIN] n_trees               : " << param_.n_trees() << std::endl;
    std::cout << "[TRAIN] max_tree_depth        : " << param_.max_tree_depth() << std::endl;
    std::cout << "[TRAIN] n_test_split_functions: " << param_.n_test_split_functions() << std::endl;
    std::cout << "[TRAIN] n_test_thresholds     : " << param_.n_test_thresholds() << std::endl;
    std::cout << "[TRAIN] n_test_samples        : " << param_.n_test_samples() << std::endl;
    std::cout << "[TRAIN] min_samples_to_split  : " << param_.min_samples_to_split() << std::endl;
  }
  
  //set up split function generator
  gen_split_fcn_->SetUp(param_.split_function_param(), samples);
  
  rv::timer::CpuTimer tim;
  tim.start();
  ForestPtr forest = boost::make_shared<Forest>();
  forest->set_n_leaf_node_fcns(gen_leaf_node_fcns_.size());
  
  #pragma omp parallel for ordered
  for(size_t treeIdx = 0; treeIdx < param_.n_trees(); ++treeIdx) {
    rv::timer::CpuTimer treetim;
    treetim.start();
    
    #pragma omp critical (TrainForest_train)
    {
      if(verbose_){
        std::cout << "[TRAIN][START] training tree " << treeIdx << " of " 
          << param_.n_trees() << std::endl;
      }
    }
    
    TrainTreePtr train_tree = boost::make_shared<TrainTreeRecursive>(treeIdx, 
        param_, gen_split_fcn_, gen_leaf_node_fcns_, split_evaluator_, verbose_); 

    TreePtr old_tree;
    if(old_forest != 0 && treeIdx < old_forest->trees_size()) {
      old_tree = old_forest->trees(treeIdx);
    }
    TreePtr tree = train_tree->Train(samples, targets, optimize_targets, train_type, old_tree);
    
    #pragma omp critical (TrainForest_train)
    {
      forest->AddTree(tree);
      if(verbose_){
        std::cout << "[TRAIN][FINISHED] training tree " << treeIdx << " of " 
          << param_.n_trees() << " - took " << treetim.stop()/ 1e3
          << "[s]" << std::endl;
        std::cout << "[TRAIN][FINISHED] " 
          << (param_.n_trees() - forest->trees_size()) 
          << " left for training" << std::endl;
      }
    }
  }
  if(verbose_){
    std::cout << "[TRAIN][FINISHED] training forest - took " 
      << tim.stop() / 1e3 << "[s]" << std::endl;
  }
  
  return forest;
}


} //ns rf
} //ns rv
