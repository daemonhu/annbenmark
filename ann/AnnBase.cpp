#include "AnnBase.h"
#include <algorithm>
#include <chrono>
#include <iostream>

AnnBase::AnnBase(const std::string& base_file_path,
                 const std::string& query_file_path,
                 const std::string& groundtruth_file_path)
    : sift_util(base_file_path, query_file_path, groundtruth_file_path) {}

int AnnBase::precision(const std::vector<int>& limits,
					   int search_para,
					   int& times,
                       std::map<int, double>& prec_sum,
                       std::map<int, double>& time_sum) {
  std::chrono::high_resolution_clock::time_point t_start, t_end;

  //******************************************************
  // std::vector<int> limits = {10, 100, 1000, 10000};
  // int K = 10;
  // int prec_n = 1000;

  // init precision and timers map
  for (auto& it : limits) {
    prec_sum[it] = 0.0;
    time_sum[it] = 0.0;
  }

  // doing the work
  const float* query_data = sift_util.get_query_vec();
  int dim = sift_util.get_dim();
  times = sift_util.get_query_vec_num();
  const std::vector<SiftGroundTruthData>& groundtruth_data =
      sift_util.get_groundtruth_data();
  std::vector<int> closest;
  std::vector<int> toplist;
  std::vector<int> intersection;
  for (int i = 0; i < times; ++i) {
    const float* vec = query_data + i * dim;
    const int* idx_vec = groundtruth_data[i].idx;

    closest.clear();
    toplist.clear();
    intersection.clear();
    closest.insert(closest.begin(), idx_vec,
                   idx_vec + groundtruth_data[i].num);
    std::sort(closest.begin(), closest.end(), std::less<int>());

    for (auto limit : limits) {
      t_start = std::chrono::high_resolution_clock::now();

      // getting the K closest
      get_nn_by_vec(vec, limit, search_para, toplist);

      t_end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start)
              .count();

      // intersecting results

      std::sort(toplist.begin(), toplist.end(), std::less<int>());
      int K = std::min((int)closest.size(), limit);
      intersection.resize(std::max(K, (int)toplist.size()));

      std::vector<int>::iterator it_set = std::set_intersection(
          closest.begin(), closest.begin() + K, toplist.begin(), toplist.end(),
          intersection.begin());
      intersection.resize(it_set - intersection.begin());

      // storing metrics
      int found = intersection.size();
      double hitrate = found / (double)K;
      prec_sum[limit] += hitrate;

      time_sum[limit] += duration;
    }
  }

  //std::cout << "\nDone" << std::endl;
  return 0;
}
