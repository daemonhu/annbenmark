#include "../util/SiftUtil.h"
#include "../ann/Annoy.h"
#include "../ann/Nsg.h"

#include <iostream>
#include<iomanip>

int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cout << argv[0] << " base_vec_path query_vec_path groundtruth_vec_path nsg_search_para" << std::endl;
        return -1;
	}

   std::vector<int> limits = {5, 10, 100, 1000};
   int times = 0;
   std::map<int, double> prec_sum;
   std::map<int, double> time_sum;
   Nsg* nsg = new Nsg(argv[1], argv[2], argv[3]);
   nsg->build(200, 200, 10, 10, 100, "./sift_base.nngraph", 40, 50, 100);
   nsg->precision(limits, std::atoi(argv[4]), times, prec_sum, time_sum);

   // print resulting metrics
   for (auto limit : limits) {
     std::cout << "limit: " << limit << "\tprecision: " << std::fixed
               << std::setprecision(4) << (100.0 * prec_sum[limit] / times)
               << "% \tavg. time: " << std::fixed << std::setprecision(6)
               << (time_sum[limit] / times) * 1e-04 << "s" << std::endl;
   }
   delete nsg;

	return 0;
}