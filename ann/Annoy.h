#pragma once
#include "AnnBase.h"

#include "kissrandom.h"
#include "annoylib.h"

#include <string>

class Annoy : public AnnBase {
 public:
  Annoy(const std::string& base_file_path, const std::string& query_file_path,
        const std::string& groundtruth_file_path);
  ~Annoy();

 public:
  int build(int tree_num);
  virtual int save_index(const std::string& file_name);
  virtual int get_nn_by_vec(const float* vec, int nn_num, int search_para,
                            std::vector<int>& closest);

 protected:
  AnnoyIndex<int, float, Euclidean, Kiss32Random>* index;
};