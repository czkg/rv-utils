// #include <rv/ml/rf/train/traintreequeued.h>

// rv::rf::TreePtr rv::rf::TrainTreeQueued::Train(std::vector< rv::rf::SamplePtr > samples, 
//                                                std::vector< rv::rf::TargetPtr > targets) {
//   std::queue<std::vector<SamplePtr> > q_samples;
//   std::queue<std::vector<TargetPtr> > q_targets;
//   std::queue<SplitNodePtr> q_parents;
//   std::queue<bool> q_left;
//   std::queue<int> q_depth;
  
//   SplitFunctionPtr best_split_fcn = OptimizeSplitFunction(samples, targets);
//   if(best_split_fcn == 0) {
//     LOG_ERROR << "bäh wäh";
//   }
//   SplitNodePtr root = boost::make_shared<SplitNode>();
//   root->set_split_fcn(best_split_fcn);
  
//   std::vector<bool> splits;
//   std::vector<SamplePtr> leftsamples, rightsamples;
//   std::vector<TargetPtr> lefttargets, righttargets;
//   Split(best_split_fcn, samples, splits);
//   Split(samples, splits, leftsamples, rightsamples);
//   Split(targets, splits, lefttargets, righttargets);
  
//   q_samples.push(leftsamples);
//   q_samples.push(rightsamples);
//   q_targets.push(lefttargets);
//   q_targets.push(righttargets);
//   q_parents.push(root);
//   q_parents.push(root);
//   q_left.push(true);
//   q_left.push(false);
//   q_depth.push(1);
//   q_depth.push(1);
  
  
//   while(q_samples.size() > 0) { 
//     samples = q_samples.front();
//     q_samples.pop();
//     targets = q_targets.front();
//     q_targets.pop();
//     SplitNodePtr parent = q_parents.front();
//     q_parents.pop();
//     bool left = q_left.front();
//     q_left.pop();
//     int depth = q_depth.front();
//     q_depth.pop();
    
//     if(depth >= param_.max_tree_depth() || samples.size() <= param_.min_samples_to_split()) {
//       NodePtr node = CreateLeafNode(targets, depth);
//       if(left) {
//         parent->set_left(node);
//       }
//       else {
//         parent->set_right(node);
//       }
//       continue;
//     }
    
//     SplitFunctionPtr best_split_fcn = OptimizeSplitFunction(samples, targets);
//     if(best_split_fcn == 0) {
//       NodePtr node = CreateLeafNode(targets, depth);
//       if(left) {
//         parent->set_left(node);
//       }
//       else {
//         parent->set_right(node);
//       }
//       continue;
//     }
    
    
//     SplitNodePtr node = boost::make_shared<SplitNode>();
//     node->set_split_fcn(best_split_fcn);
//     if(left) {
//       parent->set_left(node);
//     }
//     else {
//       parent->set_right(node);
//     }

//     Split(best_split_fcn, samples, splits);
//     Split(samples, splits, leftsamples, rightsamples);
//     Split(targets, splits, lefttargets, righttargets);
    
//     q_samples.push(leftsamples);
//     q_samples.push(rightsamples);
//     q_targets.push(lefttargets);
//     q_targets.push(righttargets);
//     q_parents.push(node);
//     q_parents.push(node);
//     q_left.push(true);
//     q_left.push(false);
//     q_depth.push(depth + 1);
//     q_depth.push(depth + 1);
//   }
  
//   return boost::make_shared<Tree>(root);
// }
