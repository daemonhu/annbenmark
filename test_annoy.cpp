#include "../util/SiftUtil.h"
#include "../ann/Annoy.h"
#include "../ann/Nsg.h"

#include <iostream>
#include<iomanip>

int main(int argc, char* argv[]) {
	if (argc != 6) {
		std::cout << argv[0] << " base_vec_path query_vec_path groundtruth_vec_path annoy_tree_num annoy_search_para" << std::endl;
        return -1;
	}

   Annoy* annoy = new Annoy(argv[1], argv[2], argv[3]);
   annoy->build(std::atoi(argv[4]));
   std::vector<int> limits = {5, 10, 100, 1000};
   int times;
   std::map<int, double> prec_sum;
   std::map<int, double> time_sum;
   annoy->precision(limits, std::atoi(argv[5]), times, prec_sum, time_sum);
   
   for (auto limit : limits) {
     std::cout << "Run " << times << " times"
			   << "limit: " << limit << "\tprecision: " << std::fixed
               << std::setprecision(4) << (100.0 * prec_sum[limit] / times)
               << "% \tavg. time: " << std::fixed << std::setprecision(6)
               << (time_sum[limit] / times) * 1e-04 << "s" << std::endl;
   }
   delete annoy;

	return 0;
}