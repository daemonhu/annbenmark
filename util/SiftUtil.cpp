#include "SiftUtil.h"

#include <iostream>

SiftUtil::SiftUtil() {}

SiftUtil::SiftUtil(const std::string& base_file_path,
                   const std::string& query_file_path,
                   const std::string groudtruth_file_path)
    : base_file_path(base_file_path),
      query_file_path(query_file_path),
      groundtruth_file_path(groudtruth_file_path),
      dim(0),
      fvec_base_vec(NULL),
      fvec_query_vec(NULL),
      fvec_base_vec_num(0),
      fvec_query_vec_num(0){
  // load base file
  load_fevc_base_file();

  // load base file
  load_fevc_query_file();

  // load ground truth file
  load_groundtruth_ivec_file();
}

SiftUtil::~SiftUtil() {
  if (fvec_base_vec) {
    delete [] fvec_base_vec;
    fvec_base_vec = NULL;
  }

  if (fvec_query_vec) {
    delete[] fvec_query_vec;
    fvec_query_vec = NULL;
  }

  for (auto& item : fvec_groundtruth_data) {
    item.destory();
  }
  fvec_groundtruth_data.clear();
}

int SiftUtil::read_sift_int(int& num, std::ifstream& input_stream) {
  num = -1;
  input_stream.read(reinterpret_cast<char*>(&num), sizeof num);
  int gcount = (int)input_stream.gcount();
  if (0 >= input_stream.gcount()) {
    return -1;
  }
  return 0;
}

template <typename T>
int SiftUtil::read_sift_vector(T* vec, std::ifstream& input_stream, int dim) {
  if (NULL == vec) {
    return -1;
  }
  input_stream.read(reinterpret_cast<char*>(vec), sizeof(T) * dim);
  if (0 >= input_stream.gcount()) {
    return -1;
  }
  return 0;
}

int SiftUtil::get_fvec_info(std::ifstream& in, int& vec_dim, int& vec_num) {
  in.read((char*)&vec_dim, 4);

  in.seekg(0, std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  vec_num = (unsigned)(fsize / (dim + 1) / 4);
  return 0;
}

int SiftUtil::load_fevc_base_file() {
  std::ifstream input_stream(base_file_path, std::ios::in | std::ios::binary);
  if (input_stream.fail()) {
    std::cout << __LINE__ << "open file " << base_file_path << " failed" << std::endl;
    return -1;
  }

  get_fvec_info(input_stream, dim, fvec_base_vec_num);
  input_stream.seekg(std::ios::beg);

  fvec_base_vec = new float[dim * fvec_base_vec_num];
  float* current_vec = fvec_base_vec;
  while (true) {
    int dim_tmp = 0;
    if (0 > read_sift_int(dim_tmp, input_stream)) {
      break;
    }

    if (0 > read_sift_vector(current_vec, input_stream, dim)) {
      break;
    }
    current_vec += dim;
  }

  input_stream.close();

  return 0;
}

int SiftUtil::load_fevc_query_file() {
  std::ifstream input_stream(query_file_path, std::ios::in | std::ios::binary);
  if (input_stream.fail()) {
    std::cout << "open query file" << query_file_path << " failed" << std::endl;
    return -1;
  }
  int dim_tmp;
  get_fvec_info(input_stream, dim_tmp, fvec_query_vec_num);
  input_stream.seekg(std::ios::beg);
  if (dim != dim_tmp) {
    std::cout << "data dim not ok base dim: " << dim << " query dim:" << dim_tmp << std::endl;
  }

  fvec_query_vec = new float[dim * fvec_query_vec_num];
  float* current_vec = fvec_query_vec;
  while (true) {
    if (0 > read_sift_int(dim_tmp, input_stream)) {
      break;
    }

    if (0 > read_sift_vector(current_vec, input_stream, dim)) {
      break;
    }
    current_vec += dim;
  }

  input_stream.close();

  return 0;
}

int SiftUtil::load_groundtruth_ivec_file() {
  std::ifstream input_stream(groundtruth_file_path,
                             std::ios::in | std::ios::binary);
  if (input_stream.fail()) {
    std::cout << __LINE__ << " open file " << groundtruth_file_path << " failed" << std::endl;
    return -1;
  }

  while (true) {
    int num = 0;
    if (0 > read_sift_int(num, input_stream)) {
      break;
    }
    SiftGroundTruthData groundtruth_data(num);
    if (0 > read_sift_vector(groundtruth_data.idx, input_stream, num)) {
      break;
    }

    fvec_groundtruth_data.push_back(groundtruth_data);
  }

  input_stream.close();

  return 0;
}

int SiftUtil::test_sift_dataset() {
  SiftUtil sift_util("./siftsmall_base.fvecs", "./siftsmall_query.fvecs",
                     "./siftsmall_groundtruth.ivecs");

  std::cout << "base fvecs vec cnt: " << sift_util.get_base_vec_num()
            << std::endl;
  std::cout << "query fvecs vec cnt: " << sift_util.get_query_vec_num()
            << std::endl;

  std::cout << "groundtruth_ivec vec cnt: "
            << sift_util.get_groundtruth_data().size() << std::endl;

  return 0;
}
