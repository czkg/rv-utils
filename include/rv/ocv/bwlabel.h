#ifndef RV_OCV_BWLABEL_H
#define RV_OCV_BWLABEL_H

#include <map>
#include <set>
#include <vector>
#include <opencv2/core/core.hpp>

namespace rv {
namespace ocv {

template <typename T>
inline T bwLabel(const cv::Mat_<T>& data, cv::Mat_<T>& labels) {
  labels = cv::Mat_<T>(data.rows, data.cols, T(0));

  std::map<T, T> label_to_min_label;

  //first pass
  T next_label = 1;
  for(int row = 0; row < data.rows; ++row) {
    for(int col = 0; col < data.cols; ++col) {

      if(data(row, col) > 0) {

        std::set<T> nb_labels;
        for(int drow = -1; drow <= 1; ++drow) {
          for(int dcol = -1; dcol <= 1; ++dcol) {
            int nrow = row + drow;
            int ncol = col + dcol;

            if(nrow >= 0 && ncol >= 0 && nrow < data.rows && ncol < data.cols &&
                labels(nrow, ncol) > 0
            ) {
              nb_labels.insert(labels(nrow, ncol));
            }
          }
        }

        if(nb_labels.size() == 0) {
          label_to_min_label[next_label] = next_label;
          labels(row, col) = next_label;
          next_label++;
        }
        else {
          //find min label
          T min_label = std::numeric_limits<T>::max();
          for(typename std::set<T>::iterator it = nb_labels.begin(); it != nb_labels.end(); ++it) {
            T label = *it;
            if(label < min_label) {
              min_label = label;
            }
          }
          if(label_to_min_label.find(minlabel) != label_to_min_label.end()) {
            min_label = label_to_min_label[min_label];
          }

          labels(row, col) = min_label;

          for(typename std::set<T>::iterator it = nb_labels.begin(); it != nb_labels.end(); ++it) {
            label_to_min_label[*it] = min_label;
          }
        } //if else has neighbour

      } //if label > 0

    } //for col in
  }// for row in

  //count labels
  std::set<T> min_labels;
  for(typename std::map<T, T>::iterator it = label_to_min_label.begin(); it != label_to_min_label.end(); ++it) {
        min_labels.insert(it->second);
  }

  std::map<T, T> final_map;
  uint finalIdx = 1;
  for(typename std::set<T>::iterator it = min_labels.begin(); it != min_labels.end(); ++it) {
    final_map[*it] = finalIdx;
    finalIdx++;
  }

  //second pas
  for(int row = 0; row < data.rows; ++row) {
    for(int col = 0; col < data.cols; ++col) {
      if(labels(row, col) > 0) {
        labels(row, col) = final_map[label_to_min_label[labels(row, col)]];
      }
    }
  }
  return min_labels.size();
}
    
} //ns cv
} //ns rv

#endif
