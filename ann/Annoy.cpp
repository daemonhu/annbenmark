#include "Annoy.h"
#include <chrono>
#include <iostream>


Annoy::Annoy(const std::string& base_file_path,
             const std::string& query_file_path,
             const std::string& groundtruth_file_path)
    : AnnBase(base_file_path, query_file_path, groundtruth_file_path) {
  
}

Annoy::~Annoy() {
	if (index) {
		delete index;
        index = NULL;
	}
}

int Annoy::build(int tree_num) {
  
  std::chrono::high_resolution_clock::time_point start, end;
  std::cout << "Building index num_trees = " << tree_num << " ...";
  start = std::chrono::high_resolution_clock::now();
  const float* base_vecs = sift_util.get_base_vec();
  int vec_num = sift_util.get_base_vec_num();
  if (0 >= vec_num) {
    std::cout << "base vec empty" << std::endl;
  }
  index = new AnnoyIndex<int, float, Euclidean, Kiss32Random>(sift_util.get_dim());

  for (int i = 0; i < vec_num;++i) {
    index->add_item(i, base_vecs + i * sift_util.get_dim());
  }
  
  index->build(tree_num);
  end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << " Done in " << duration << " secs." << std::endl;

  return 0;
}

int Annoy::get_nn_by_vec(const float* vec, int nn_num, int search_para,
                         std::vector<int>& toplist) {
  index->get_nns_by_vector(vec, nn_num, search_para, &toplist, NULL);
  return 0;
}

int Annoy::save_index(const std::string& file_name) { 
	if (index->save(file_name.c_str())) 	{
		return 0;
	} else {
		std::cout << "save index failed" << std::endl;
		return -1;
	}
}
