#pragma once
#include "AnnBase.h"
#include "efanna2e/index_nsg.h"
#include "efanna2e/util.h"

#include <string>

class Nsg : public AnnBase {
 public:
  Nsg(const std::string& base_file_path, const std::string& query_file_path,
        const std::string& groundtruth_file_path);
  ~Nsg();

 public:
  int build(unsigned nnK, unsigned nnL, unsigned nnIter, unsigned nnS,
            unsigned nnR, const std::string& nn_graph_file, unsigned L,
            unsigned R, unsigned C);
  virtual int save_index(const std::string& file_name);
  virtual int get_nn_by_vec(const float* vec, int n, int K,
                            std::vector<int>& closest);

 protected:
  int genernate_nn_graph(unsigned K, unsigned L, unsigned iter,
                         unsigned S, unsigned R,
                         const std::string& nn_graph_file);

 protected:
  efanna2e::IndexNSG* index;
};