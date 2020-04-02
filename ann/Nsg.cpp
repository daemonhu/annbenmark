#include "Nsg.h"
#include <efanna2e/neighbor.h>
#include <efanna2e/index_graph.h>
#include <efanna2e/index_random.h>
#include <efanna2e/util.h>

#include <chrono>
#include <iostream>


Nsg::Nsg(const std::string& base_file_path,
             const std::string& query_file_path,
             const std::string& groundtruth_file_path)
    : AnnBase(base_file_path, query_file_path, groundtruth_file_path), index(NULL) {
}

Nsg::~Nsg() {
	if (index) {
		delete index;
        index = NULL;
	}
}

int Nsg::build(unsigned nnK, unsigned nnL, unsigned nnIter,
               unsigned nnS, unsigned nnR, 
	           const std::string& nn_graph_file,
			   unsigned L, unsigned R, unsigned C) {
  
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
  const float* data_load = sift_util.get_base_vec();
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
  index->OptimizeGraph(const_cast<float*>(data_load));
  auto e = std::chrono::high_resolution_clock::now();

  end = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "Build Done in " << duration << " secs." << std::endl;

  return 0;
}

int Nsg::get_nn_by_vec(const float* vec, int nn_num, int search_para,
                       std::vector<int>& toplist) {
  efanna2e::Parameters paras;
  paras.Set<unsigned>("L_search", search_para);
  paras.Set<unsigned>("P_search", search_para);
  toplist.resize(nn_num);
  index->SearchWithOptGraph(vec, nn_num, paras, (unsigned*)toplist.data());
  
  return 0;
}

int Nsg::save_index(const std::string& file_name) { 
	index->Save(file_name.c_str());
    return 0;
}

int Nsg::genernate_nn_graph(unsigned K, unsigned L, 
	unsigned iter, unsigned S, unsigned R, const std::string& nn_graph_file) {

  const float* data_load = sift_util.get_base_vec();
  unsigned int points_num = sift_util.get_base_vec_num();
  unsigned int dim = sift_util.get_dim();
 
  // data_load = efanna2e::data_align(data_load, points_num, dim);//one must
  // align the data before build
  efanna2e::IndexRandom init_index(dim, points_num);
  efanna2e::IndexGraph graph_index(dim, points_num, efanna2e::L2,
                             (efanna2e::Index*)(&init_index));

  efanna2e::Parameters paras;
  paras.Set<unsigned>("K", K);
  paras.Set<unsigned>("L", L);
  paras.Set<unsigned>("iter", iter);
  paras.Set<unsigned>("S", S);
  paras.Set<unsigned>("R", R);

  auto s = std::chrono::high_resolution_clock::now();
  graph_index.Build(points_num, data_load, paras);
  auto e = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = e - s;
  std::cout << "Time cost: " << diff.count() << "\n";

  graph_index.Save(nn_graph_file.c_str());

  return 0;
}
