#pragma once

#include <fstream>
#include <vector>

struct SiftGroundTruthData {
 public:
  SiftGroundTruthData(int num) : num(num) {
    idx = new int[num];
  }
  void destory() {
    if (idx) {
      delete[] idx;
      idx = NULL;
    }
  }
 public:
  int num;
  int* idx;
};

// todo it's not perfect code, i will improve this later
class SiftUtil {
 public:
  SiftUtil();
  SiftUtil(const std::string& base_file_path,
           const std::string& query_file_path,
           const std::string groudtruth_file_path);
  ~SiftUtil();

 public:
  int get_dim() { return dim; }
  int get_base_vec_num() { return fvec_base_vec_num; }
  const float* get_base_vec() { return fvec_base_vec; }
  int get_query_vec_num() { return fvec_query_vec_num; }
  const float* get_query_vec() { return fvec_query_vec; }
  const std::vector<SiftGroundTruthData>& get_groundtruth_data() {
    return fvec_groundtruth_data;
  }
  static int test_sift_dataset();

 private:
  int get_fvec_info(std::ifstream& in, int& vec_dim, int& vec_num);
  int load_fevc_base_file();

  int load_fevc_query_file();

  int load_groundtruth_ivec_file();

  template <typename T>
  int read_sift_vector(T* vec, std::ifstream& input_stream, int dim);

  int read_sift_int(int& num, std::ifstream& input_stream);

 private:
  std::string base_file_path;
  std::string query_file_path;
  std::string groundtruth_file_path;

  int dim;
  int fvec_base_vec_num;
  float* fvec_base_vec = nullptr;
  int fvec_query_vec_num;
  float* fvec_query_vec = nullptr;
  std::vector<SiftGroundTruthData> fvec_groundtruth_data;
};
