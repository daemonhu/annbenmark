#pragma once
#include "AnnBase.h"
#include "efanna2e/index_nsg.h"
#include "efanna2e/neighbor.h"
#include "efanna2e/util.h"

#include <string>

class Nsg : public AnnBase {
public:
  Nsg() = default;
  Nsg(const std::string &base_file_path, const std::string &query_file_path,
      const std::string &groundtruth_file_path);
  Nsg(int dim, unsigned K, unsigned L1, unsigned iter, unsigned S, unsigned R1,
      unsigned L2, unsigned R2, unsigned C);
  virtual ~Nsg();

public:
  int build(unsigned nnK, unsigned nnL, unsigned nnIter, unsigned nnS,
            unsigned nnR, const std::string &nn_graph_file, unsigned L,
            unsigned R, unsigned C);
  int build();
  int addAll(const std::vector<std::vector<float>> &queries);
  virtual int save_index(const std::string &file_name);
  virtual int get_nn_by_vec(const float *vec, int n, int K,
                            std::vector<int> &closest);
  int load(const std::string &data_path, const std::string &nsg_path);

  int close();
  int optimizeGraph();
  int save(const std::string &data_path, const std::string &nsg_path);
  std::vector<efanna2e::Neighbor> search(const std::vector<float> &query,
                                         unsigned L, unsigned K);
  std::vector<efanna2e::Neighbor>
  searchWithOptGraph(const std::vector<float> &query, unsigned L, unsigned K);
  std::vector<float> &data();

protected:
  int genernate_nn_graph(unsigned K, unsigned L, unsigned iter, unsigned S,
                         unsigned R, const std::string &nn_graph_file);

protected:
  efanna2e::IndexNSG *index = nullptr;

private:
  int save_data(const std::string &data_path);
  int load_data(const std::string &data_path);
  int load_index(const std::string &nsg_path);

private:
  int dim_ = 0;
  unsigned K_ = 0;
  unsigned L1_ = 0;
  unsigned I_ = 0;
  unsigned S_ = 0;
  unsigned R1_ = 0;
  unsigned L2_ = 0;
  unsigned R2_ = 0;
  unsigned C_ = 0;
  std::vector<float> data_;
  size_t data_size_ = 0;
};
