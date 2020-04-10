#pragma once

#include "../util/SiftUtil.h"
#include <map>

class AnnBase {
 public:
	AnnBase() = default;
	AnnBase(const std::string& base_file_path, const std::string& query_file_path,
          const std::string& groundtruth_file_path);
 public:
    virtual int get_nn_by_vec(const float* vec, int nn_num, int search_para, std::vector<int>& closest) = 0;
	virtual int save_index(const std::string& file_name) = 0;

	int precision(const std::vector<int>& limits, 
				  int search_para,
				  int& times,
                  std::map<int, double>& prec_sum,
                  std::map<int, double>& time_sum);
	virtual ~AnnBase() = default;
 protected:
	SiftUtil sift_util;
};

