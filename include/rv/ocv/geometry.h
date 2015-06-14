#ifndef RV_OCV_GEOMETRY_H
#define RV_OCV_GEOMETRY_H

#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <rv/stat/core.h>
#include <rv/log/log.h>

namespace rv {
namespace cv {

enum PCL2DM_TYPE {
  PCL2DM_MIN, 
  PCL2DM_MEAN, 
  PCL2DM_MEDIAN
};

enum PROJECTION_TYPE {
    PROJECTIVE, 
    ORTHOGRAPHIC
};

template <typename T> 
void cameraMotion(cv::Mat_<T>& P, cv::Mat_<T>& K, cv::Mat_<T>& R, cv::Mat_<T>& C) {
  //null space of P
  cv::Mat_<T> w, u, vt;
  cv::SVD::compute(P, w, u, vt, cv::SVD::FULL_UV);
  C = vt.t();
  C = C.colRange(3, 4) / C(3, 3);

  cv::Mat_<T> K_sign;

  cv::Mat_<T> Psub = P.colRange(0,3);

  cv::RQDecomp3x3(Psub, K, R);

  K_sign = K.diag(0).clone();

  cv::pow(K_sign, 0, K_sign);

  K_sign = cv::Mat::diag(K_sign);

  K = K*K_sign;
  R = R*K_sign;

  K = K / K(2,2);

  K(1,0) = (T)0.0;
  K(0,1) = (T)0.0;
  K(2,0) = (T)0.0;
  K(2,1) = (T)0.0;
}

template <typename T> void normalizePoints(cv::Mat_<T>& pts) {
  int norm_row;

  if(pts.rows == 3) {
    norm_row = 2;
  }
  else if(pts.rows == 4) {
    norm_row = 3;
  }
  else {
    LOG_ERROR << "normalizePoints homogenious point clouds must be of size 3xN or 4xN";
  }

  for(int row = 0; row < pts.rows; ++row) {
    for(int col = 0; col < pts.cols; ++col) {
      pts(row, col) = pts(row, col) / pts(norm_row, col);
    }
  }
}

template <typename T>
cv::Mat_<T> pointcloud2Depthmap(cv::Mat_<T>& pts3, cv::Mat_<T>& P, int M, int N, 
                                std::vector<T> projection_vals = std::vector<T>(),
                                T missing_value = -1, 
                                PCL2DM_TYPE type = PCL2DM_MEDIAN, 
                                PROJECTION_TYPE proj_type = PROJECTIVE) {
  //null space of P
  cv::Mat_<T> w, u, vt;
  cv::SVD::compute(P, w, u, vt, cv::SVD::FULL_UV);
  cv::Mat_<T> C = vt.t();
  C = C.colRange(3, 4) / C(3, 3);

  //compute depths
  std::vector<std::vector<std::vector<T> > > depths(M, std::vector<std::vector<T> >(N));

  if(proj_type == PROJECTIVE) {
    cv::Mat_<T> pts2 = P * pts3;
    normalizePoints(pts2);

    for(int col = 0; col < pts3.cols; ++col) {
      T dx = C(0, 0) - pts3(0, col);
      T dy = C(1, 0) - pts3(1, col);
      T dz = C(2, 0) - pts3(2, col);
      T d = std::sqrt( dx*dx + dy*dy + dz*dz );

      int x = round( pts2(0, col) );
      int y = round( pts2(1, col) );

      if((x >= 0) && (y >= 0) && (x < N) && (y < M)) {
        depths[y][x].push_back(d);
      }
    }
  }
  else if (proj_type == ORTHOGRAPHIC) {
    cv::Mat_<T> K, R;
    cameraMotion(P, K, R, C);

    cv::Mat_<T> pts33 = pts3.rowRange(0,3);

    for(int col = 0; col < pts3.cols; ++col) {
      pts3.col(col) = (pts3.col(col) - C);
    }

    cv::Mat_<T> pts33_cam = R*(pts33 - cv::repeat(C.rowRange(0,3),1, pts33.cols));
    cv::Mat_<T> pts2 = K * pts33_cam;

    normalizePoints(pts2);

    cv::Mat_<T> d = pts33_cam.row(2);

    for(int col = 0; col < d.cols; ++col) {
      int x = round( pts2(0, col) );
      int y = round( pts2(1, col) );

      if((x >= 0) && (y >= 0) && (x < N) && (y < M)) {
        depths[y][x].push_back(d(col));
      }
    }
  } else {
    LOG_ERROR << "projection type " << proj_type << " not supported";
  }

  //depth values to image
  cv::Mat_<T> depth(M, N, missing_value);
  for(int row = 0; row < depth.rows; ++row) {
    for(int col = 0; col < depth.cols; ++col) {
      if(depths[row][col].size() == 0) continue;
      
      T d = missing_value;
      switch(type) {
        case PCL2DM_MIN:
          d = rv::min(depths[row][col]);
          break;
        case PCL2DM_MEAN:
          d = rv::mean(depths[row][col]);
          break;
        case PCL2DM_MEDIAN:
          d = rv::median(depths[row][col]);
          break;
      }
      depth(row, col) = d;
    }
  }
  
  return depth;
}

template <typename T>
cv::Mat_<T> depthMap2pointCloud(cv::Mat_<T>& depth, cv::Mat_<T>& P,
                                T missing_value = -1,
                                PROJECTION_TYPE proj_type = PROJECTIVE) {
  //reproject points
  if(P.cols == 3) {
    P.col(4) = 0;
  }

  cv::Mat_<T> C, K, R;
  cameraMotion(P, K, R, C);

  int M = depth.rows;
  int N = depth.cols;

  cv::Mat_<T> pts3(4,M*N);
  cv::Mat_<T> lines3(3,M*N);
  cv::Mat_<T> pts2(3,M*N);

  cv::Mat_<T> K_inv = K.inv();

  std::cout << "K = " << K << std::endl;
  std::cout << "K_inv = " << K_inv << std::endl;
//    cv::Mat_<T> pt2(3,1);
  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      pts2(0,m*N+n) = n;
      pts2(1,m*N+n) = m;
      pts2(2,m*N+n) = (T)1.0;
    }
  }

  lines3 = K_inv*pts2;

  if(proj_type == PROJECTIVE) {
    T norm;
    for(int i = 0; i < lines3.cols; i++) {
      norm = sqrt(pow(lines3(0,i),(T)2.f) + pow(lines3(1,i),(T)2.f) + pow(lines3(2,i),(T)2.f));
      lines3.col(i) = lines3.col(i)/norm;
    }
  }

//    cv::Mat_<T> d2 = cv::repeat(depth.reshape(0,1), 3, 1);
//    std::cout << "d2 [ " << d2.rows << " x " << d2.cols << " ] " << std::endl;
  cv::multiply(lines3, cv::repeat(depth.reshape(0,1), 3, 1), pts3);
  pts3 = R.t()*pts3 + cv::repeat(C.rowRange(0,3),1, pts3.cols);

  return pts3;
}

}
}//namespace


#endif
