#ifndef RV_OCV_VISUALIZE_H
#define RV_OCV_VISUALIZE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <rv/ocv/color.h>
#include <rv/log/log.h>

namespace rv {
namespace ocv {

  
inline void imshow(std::string windowname, cv::Mat_<cv::Vec3b> img, float scale = 1.0, int interpolation = CV_INTER_NN) {
  cv::Mat_<cv::Vec3b> scaledImg;
  if(scale != 1.0) {
    cv::resize(img, scaledImg, cv::Size(img.cols * scale, img.rows * scale), 0, 0, interpolation);
  }
  else {
    scaledImg = img;
  }
  cv::imshow(windowname, scaledImg);
}


template <typename PointType>
inline void drawPoints(cv::Mat_<cv::Vec3b>& img, const std::vector<cv::Point_<PointType> >& points, const std::vector<cv::Scalar>& colors, int radius = 4, int thickness = -1) {
  for(size_t i = 0; i < points.size(); ++i) {
    cv::Point2i pt(points[i].x, points[i].y);
    cv::circle(img, pt, radius, colors[i], thickness);
  }
}


template <typename PointType>
inline void drawPoints(cv::Mat_<cv::Vec3b>& img, const std::vector<cv::Point_<PointType> >& points, const cv::Scalar color, int radius = 4, int thickness = -1) {
  for(size_t i = 0; i < points.size(); ++i) {
    cv::Point2i pt(points[i].x, points[i].y);
    cv::circle(img, pt, radius, color, thickness);
  }
}


template <typename PointType>
inline void drawMask(cv::Mat_<cv::Vec3b>& img, const std::vector<cv::Point_<PointType> >& points, const cv::Vec3b color, float alpha = 0.75) {
  cv::Rect roi(0, 0, img.cols, img.rows);

  for(size_t i = 0; i < points.size(); ++i) {
    cv::Point2i pt(points[i].x, points[i].y);

    if(!roi.contains(pt)) {
      LOG_ERROR << "point [" << pt.x << ", " << pt.y << "] is not in img [" << img.cols << ", " << img.rows << "]";
    }

    cv::Vec3b pxIn = img(pt.y, pt.x);

    cv::Vec3b pxOut(
      alpha * color(0) + (1 - alpha) * pxIn(0),
      alpha * color(1) + (1 - alpha) * pxIn(1),
      alpha * color(2) + (1 - alpha) * pxIn(2)
    );

    img(pt.y, pt.x) = pxOut;
  }
}

template <typename T>
inline cv::Mat_<T> blend(const cv::Mat_<T>& img1, const cv::Mat_<T>& img2, float alpha) {
  cv::Mat_<T> res(img1.rows, img2.cols);

  for(int row = 0; row < img1.rows; ++row) {
    for(int col = 0; col < img1.cols; ++col) {
      res(row, col) = alpha * img1(row, col) + (1 - alpha) * img2(row, col);
    }
  }

  return res;
}


template <typename T>
inline cv::Mat_<T> combine(const std::vector<cv::Mat_<T> >& imgs, size_t rows, size_t cols ) {
  if(imgs.size() > rows * cols) {
    LOG_ERROR << "number of imgs != rows * cols in ocvCombine";
  }

  size_t imgrows = imgs.at(0).rows;
  size_t imgcols = imgs.at(0).cols;
  size_t matrows = imgrows;
  size_t matcols = imgcols;

  cv::Mat_<T> ret(matrows * rows, matcols * cols, -1);

  size_t imgIdx = 0;
  for(size_t row = 0; row < rows; ++row) {
    for(size_t col = 0; col < cols; ++col) {
      cv::Mat_<T> img;
      if(imgIdx < imgs.size()) {
        img = imgs[imgIdx];
      } else {
        img = cv::Mat_<T>(imgrows, imgcols);
      }
      imgIdx++;

      for(size_t matrow = 0; matrow < matrows; ++matrow) {
        for(size_t matcol = 0; matcol < matcols; ++matcol) {
          ret(row * matrows + matrow, col * matcols + matcol) = img(matrow, matcol);
        }
      }
    }
  }

  return ret;
}


inline cv::Mat_<cv::Vec3b> label2Bgr(const cv::Mat_<unsigned int>& labels, unsigned int nLabels, cv::Vec3b bg = cv::Vec3b(255, 255, 255)) {
  cv::Mat_<cv::Vec3b> bgr(labels.rows, labels.cols);

  std::vector<cv::Scalar> colors = hsv(nLabels);
  for(int row = 0; row < labels.rows; ++row) {
    for(int col = 0; col < labels.cols; ++col) {
      unsigned int label = labels(row, col);

      if(label > 0) {
          cv::Scalar color = colors[(label - 1) % nLabels];
        bgr(row, col) = cv::Vec3b(color(0), color(1), color(2));
      }
      else {
        bgr(row, col) = bg;
      }
    }
  }

  return bgr;
}
  
  
} //ns cv
} //ns rv

#endif
