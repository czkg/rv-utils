#ifndef RV_OCV_MEANSHIFT_H
#define RV_OCV_MEANSHIFT_H

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/flann/flann.hpp>

#include <rv/ocv/linalg.h>


namespace rv {
namespace ocv {
 
template <typename Dtype, int N>
inline std::vector<cv::Vec<Dtype, N> > meanshift(const std::vector<cv::Vec<Dtype, N> >& pts, 
                                                 const cv::Vec<Dtype, N>& init, double bandwidth, 
                                                 double neighbourhood, int max_iters, double eps,
                                                 std::vector<int>& idx) {
  typedef cv::Vec<Dtype, N> V;
  
  V mx = init;
//     std::cout << "mx: " << mx << std::endl;
  
  std::vector<V> centers;
  centers.push_back(mx);
  for(int iter = 0; iter < max_iters; ++iter) {    
    idx.clear();
    
    V term1 = 0;
    double term2 = 0;
    
    for(size_t pts_idx = 0; pts_idx < pts.size(); ++pts_idx) {
      V pt = pts[pts_idx];
      double dist = dist2(mx, pt);
      double K = std::exp(-bandwidth * dist);
//             double K = 3.0 / 4.0 * (1 - dist);
      
      if(K > neighbourhood) {
        term1 = term1 + K * pt;
        term2 = term2 + K;
      }
    }
    
    V mx_new = term1 * (1.0 / term2);
    
    double dist = dist2(mx, mx_new);
    mx = mx_new;
    centers.push_back(mx);
    
    if(dist < eps || iter == max_iters - 1) {
      for(size_t pts_idx = 0; pts_idx < pts.size(); ++pts_idx) {
        double dist = dist2(mx, pts[pts_idx]);
        double K = std::exp(-bandwidth * dist);
        
        if(K > neighbourhood) {
          idx.push_back(pts_idx);
        }
      }
      
      break;
    }
  }
  
  return centers;
}
 
template <typename Dtype>
inline void meanshift(const cv::Mat_<Dtype>& pts, 
                      const cv::Mat_<Dtype>& init, double bandwidth, 
                      int max_iters,
                      std::vector<int>& idx) {        
  //parameter set up
  bandwidth *= bandwidth;
  Dtype stop_threshold = 1e-4 * bandwidth;
  
  int n_dim = pts.cols;;
  
  //set up flann
  cv::Mat_<int> indices(1, pts.rows);
  cv::Mat_<float> distances(1, pts.rows);
  
  cvflann::LinearIndexParams flann_params;
  cvflann::SearchParams search_params(pts.rows);
  cv::flann::GenericIndex<cvflann::L2<Dtype> > nbrs(pts, flann_params);
  
  //mean shift
  cv::Mat_<Dtype> my_mean = init.clone();
  for(int iter = 0; iter < max_iters; ++iter) {    
    //find nbrs
    int nbrs_count = nbrs.radiusSearch(my_mean, indices, distances, bandwidth, search_params);
    
    //backup old mean
    cv::Mat_<Dtype> my_old_mean = my_mean.clone();
    
    //compute mean from nbrs
    my_mean = cv::Mat_<Dtype>(1, n_dim, Dtype(0));
    for(int nbr_idx = 0; nbr_idx < nbrs_count; ++nbr_idx) {
        my_mean += pts.row(indices(0, nbr_idx));
    }
    my_mean = my_mean / Dtype(nbrs_count);
            
    //check convergence
    Dtype dist = rv::ocv::dist2(my_old_mean, my_mean)(0, 0);
    
    if(dist < stop_threshold || iter == max_iters - 1) {
      for(int nbr_idx = 0; nbr_idx < nbrs_count; ++nbr_idx) {
        idx.push_back(indices(0, nbr_idx));
      }
      break;
    }
  }
}



template <typename Dtype>
struct mean_t {
  cv::Mat_<Dtype> mean;
  int n_nbrs;
  
  mean_t(cv::Mat_<Dtype> m, int n) : mean(m), n_nbrs(n) {}
  
  bool operator<(const mean_t& other) const {
    return n_nbrs < other.n_nbrs;
  }
};

template <typename Dtype>
inline void meanshiftSegmentation(const cv::Mat_<Dtype>& pts, 
                                  const cv::Mat_<Dtype>& seeds,
                                  std::vector<int>& labels, cv::Mat_<Dtype>& centers,
                                  int max_iters = 100, Dtype bandwidth = 50) {
  int n_samples = pts.rows;
  int n_dim = pts.cols;
  
  bandwidth *= bandwidth;
  Dtype stop_threshold = 1e-4 * bandwidth;
  
  std::vector<mean_t<Dtype> > means;
  cv::Mat_<int> indices(1, pts.rows);
  cv::Mat_<float> distances(1, pts.rows);
  
  cvflann::LinearIndexParams flann_params;
  cvflann::SearchParams search_params(n_samples);
  cv::flann::GenericIndex<cvflann::L2<Dtype> > nbrs(pts, flann_params);
  
  for(int seed_row = 0; seed_row < seeds.rows; ++seed_row) {
  
    int nbrs_count = -1;
    cv::Mat_<Dtype> my_mean = seeds.row(seed_row).clone();
    for(int iter = 0; iter < max_iters; ++iter) {    
      //find nbrs
      nbrs_count = nbrs.radiusSearch(my_mean, indices, distances, bandwidth, search_params);
      
      //backup old mean
      cv::Mat_<Dtype> my_old_mean = my_mean.clone();
      
      //compute mean from nbrs
      my_mean = cv::Mat_<Dtype>(1, n_dim, Dtype(0));
      for(int nbr_idx = 0; nbr_idx < nbrs_count; ++nbr_idx) {
          my_mean += pts.row(indices(0, nbr_idx));
      }
      my_mean = my_mean / Dtype(nbrs_count);
      
      //check convergence
      Dtype dist = dist2(my_old_mean, my_mean)(0, 0);
      if(dist < stop_threshold) {
        break;
      }
    }
      
    means.push_back(mean_t<Dtype>(my_mean, nbrs_count));
  }
  
  
  //postprocess remove near centers
  std::sort(means.begin(), means.end());
  std::reverse(means.begin(), means.end());
  
  std::vector<cv::Mat_<Dtype> > unique_means;
  for(size_t i = 0; i < means.size(); ++i) {
    cv::Mat_<Dtype> mean = means[i].mean;
    bool unique = true;
    
    for(size_t j = 0; j < unique_means.size(); ++j) {
      Dtype dist = dist2(mean, unique_means[j])(0, 0);
      dist *= dist;
      if(dist < bandwidth) {
        unique = false;
        break;
      }
    }
    
    if(unique) {
      unique_means.push_back(mean);
    }
  }
  
  //vec to mat
  centers = cv::Mat_<Dtype>(unique_means.size(), n_dim);
  for(int row = 0; row < centers.rows; ++row) {
    for(int col = 0; col < centers.cols; ++col) {
      centers(row, col) = unique_means[row](0, col);
    }   
  }
  
  //assign points to the nearest centers
  cvflann::LinearIndexParams mean_nbrs_params;
  cvflann::SearchParams mean_nbrs_search_params(1);
  cv::flann::GenericIndex<cvflann::L2<Dtype> > mean_nbrs(centers, mean_nbrs_params);
  labels.resize(pts.rows);
  
  for(int row = 0; row < pts.rows; ++row) {    
    mean_nbrs.knnSearch(pts.row(row), indices, distances, 1, mean_nbrs_search_params);
    labels[row] = indices(0, 0);
  }
}



} //ns cv
} //ns rv


#endif
