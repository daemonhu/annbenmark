#include "Nsg.h"
#include "efanna2e/parameters.h"
#include <efanna2e/index_graph.h>
#include <efanna2e/index_random.h>
#include <efanna2e/neighbor.h>
#include <efanna2e/util.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <cassert>

Nsg::Nsg(const std::string &base_file_path, const std::string &query_file_path,
         const std::string &groundtruth_file_path)
    : AnnBase(base_file_path, query_file_path, groundtruth_file_path),
      index(nullptr) {}

Nsg::Nsg(int dim, unsigned K, unsigned L1, unsigned iter, unsigned S,
         unsigned R1, unsigned L2, unsigned R2, unsigned C)
    : dim_(dim), K_(K), L1_(L1), I_(iter), S_(S), R1_(R1), L2_(L2), R2_(R2),
      C_(C), index(nullptr) {
  assert(L1 >= K);
}

Nsg::~Nsg() {
  if (index) {
    delete index;
    index = nullptr;
  }
}

int Nsg::close() {
  data_.clear();
  if (index) {
    delete index;
    index = nullptr;
  }
}

int Nsg::optimizeGraph() { index->OptimizeGraph(data_.data()); }

int Nsg::save(const std::string &data_path, const std::string &nsg_path) {
  int ret = 0;
  if ((ret = save_data(data_path))) {
    std::cerr << "ERR save data to " << data_path << std::endl;
    return ret;
  }
  if ((ret = save_index(nsg_path))) {
    std::cerr << "ERR save index to " << data_path << std::endl;
    return ret;
  }
  return 0;
}

std::vector<float> &Nsg::data() { return data_; }

int Nsg::load(const std::string &data_path, const std::string &nsg_path) {
	if (load_data(data_path)) {
	  std::cerr << "ERROR load " << data_path << std::endl;
	  return -1;
	}
	return load_index(nsg_path);
}

int Nsg::load_index(const std::string &nsg_path) {
  if (index) {
    delete index;
	index = nullptr;
  }
  index = new efanna2e::IndexNSG(dim_, data_size_, efanna2e::L2, nullptr);
  index->Load(nsg_path.c_str());
  return 0;
}

int Nsg::load_data(const std::string &data_path) {
  // load data with sift10K pattern
  std::ifstream in(data_path, std::ios::binary);
  if (!in.is_open()) {
    std::cerr << "open file error" << std::endl;
	return -1;
  }
  in.read((char *)&dim_, 4);
  // std::cout<<"data dimension: "<<dim<<std::endl;
  in.seekg(0, std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  data_size_ = (unsigned)(fsize / (dim_ + 1) / 4);
  data_.resize((size_t)data_size_ * (size_t)dim_);

  in.seekg(0, std::ios::beg);
  for (size_t i = 0; i < data_size_; i++) {
    in.seekg(4, std::ios::cur);
    in.read((char *)(&data_[0] + i * dim_), dim_ * 4);
  }
  in.close();
  return 0;
}

int Nsg::save_data(const std::string &data_path) {
  std::ofstream out(data_path, std::ios::binary | std::ios::out);

  for (unsigned i = 0; i < data_size_; i++) {
    out.write((const char *)&dim_, sizeof(unsigned));
    out.write((const char *)&data_[i * dim_], dim_ * sizeof(float));
  }
  out.close();
  return 0;
}

int Nsg::addAll(const std::vector<std::vector<float>>& queries) {
  data_size_ += queries.size();
  for (auto &&query : queries) {
    data_.insert(data_.end(), query.begin(), query.end());
  }
}

int Nsg::build() {
  if (data_size_ == 0) {
    return 0;
  }
  std::chrono::high_resolution_clock::time_point start, end;
  std::cout << "generating nn graph..." << std::endl;
  start = std::chrono::high_resolution_clock::now();
  std::string nn_graph_file;
  char buffer[L_tmpnam] = {0};
  std::tmpnam(buffer);
  nn_graph_file = buffer;
  genernate_nn_graph(K_, L1_, I_, S_, R1_, nn_graph_file);
  end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "generating nn graph finished in " << duration << " secs\n";

  std::cout << "Building index ..." << std::endl;
  start = std::chrono::high_resolution_clock::now();
  index = new efanna2e::IndexNSG(dim_, data_size_, efanna2e::L2, nullptr);

  auto s = std::chrono::high_resolution_clock::now();
  efanna2e::Parameters paras;
  paras.Set<unsigned>("L", L2_);
  paras.Set<unsigned>("R", R2_);
  paras.Set<unsigned>("C", C_);
  paras.Set<std::string>("nn_graph_path", nn_graph_file);

  index->Build(data_size_, data_.data(), paras);
  auto e = std::chrono::high_resolution_clock::now();

  end = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "Build Done in " << duration << " secs." << std::endl;
  if (std::remove(nn_graph_file.c_str())) {
    std::cerr << "ERROR remove " << nn_graph_file << std::endl;
  }

  return 0;
}

int Nsg::build(unsigned nnK, unsigned nnL, unsigned nnIter, unsigned nnS,
               unsigned nnR, const std::string &nn_graph_file, unsigned L,
               unsigned R, unsigned C) {

  std::chrono::high_resolution_clock::time_point start, end;

  std::cout << "generating nn graph..." << std::endl;
  start = std::chrono::high_resolution_clock::now();
  genernate_nn_graph(nnK, nnL, nnIter, nnS, nnR, nn_graph_file);
  end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "generating nn graph finished in " << duration << " secs";

  std::cout << "Building index ..." << std::endl;
  start = std::chrono::high_resolution_clock::now();
  const float *data_load = sift_util.get_base_vec();
  unsigned int points_num = sift_util.get_base_vec_num();
  unsigned int dim = sift_util.get_dim();
  index = new efanna2e::IndexNSG(dim, points_num, efanna2e::L2, nullptr);

  auto s = std::chrono::high_resolution_clock::now();
  efanna2e::Parameters paras;
  paras.Set<unsigned>("L", L);
  paras.Set<unsigned>("R", R);
  paras.Set<unsigned>("C", C);
  paras.Set<std::string>("nn_graph_path", nn_graph_file);

  index->Build(points_num, data_load, paras);
  index->OptimizeGraph(const_cast<float *>(data_load));
  auto e = std::chrono::high_resolution_clock::now();

  end = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "Build Done in " << duration << " secs." << std::endl;

  return 0;
}

std::vector<efanna2e::Neighbor> Nsg::search(const std::vector<float> &query,
                                            unsigned L, unsigned K) {
  std::vector<efanna2e::Neighbor> result;
  if (L < K) {
	  std::cerr << "ERROR L:" << L << " is smaller than K:" << K << std::endl;
	  return result;
  }
  index->Search(query.data(), data_.data(), K, L, result);
  return result;
}

std::vector<efanna2e::Neighbor>
Nsg::searchWithOptGraph(const std::vector<float> &query, unsigned L,
                        unsigned K) {
  std::vector<efanna2e::Neighbor> result;
  if (L < K) {
	  std::cerr << "ERROR L:" << L << " is smaller than K:" << K << std::endl;
	  return result;
  }
  index->SearchWithOptGraph(query.data(), K, L, result);
  return result;
}

int Nsg::get_nn_by_vec(const float *vec, int nn_num, int search_para,
                       std::vector<int> &toplist) {
  efanna2e::Parameters paras;
  paras.Set<unsigned>("L_search", search_para);
  paras.Set<unsigned>("P_search", search_para);
  toplist.resize(nn_num);
  index->SearchWithOptGraph(vec, nn_num, paras, (unsigned *)toplist.data());

  return 0;
}

int Nsg::save_index(const std::string &nsg_path) {
  index->Save(nsg_path.c_str());
  return 0;
}

int Nsg::genernate_nn_graph(unsigned K, unsigned L, unsigned iter, unsigned S,
                            unsigned R, const std::string &nn_graph_file) {

  const float* data_load = sift_util.get_base_vec();
  unsigned int points_num = sift_util.get_base_vec_num();
  unsigned int dim = sift_util.get_dim();

  // data_load = efanna2e::data_align(data_load, points_num, dim);//one must
  // align the data before build
  efanna2e::IndexRandom init_index(dim_, data_size_);
  efanna2e::IndexGraph graph_index(dim_, data_size_, efanna2e::L2,
                                   (efanna2e::Index *)(&init_index));

  efanna2e::Parameters paras;
  paras.Set<unsigned>("K", K);
  paras.Set<unsigned>("L", L);
  paras.Set<unsigned>("iter", iter);
  paras.Set<unsigned>("S", S);
  paras.Set<unsigned>("R", R);

  auto s = std::chrono::high_resolution_clock::now();
  // graph_index.Build(points_num, data_load, paras);
  float *data = new float[data_size_ * dim_];
  for (size_t i = 0; i < data_size_ * dim_; ++i) {
    data[i] = data_[i];
  }
  graph_index.Build(data_size_, data, paras);
  auto e = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = e - s;
  std::cout << "Time cost: " << diff.count() << "\n";

  graph_index.Save(nn_graph_file.c_str());

  return 0;
}
