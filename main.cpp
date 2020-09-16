#include "ann.h"

int main() {


  ANN_wrap <double> wrap ("housepricedata.csv", 1, 0.7, 10,
                          "network_parameters.dat", DB_BITS*3/4,
                          "output.csv");

  for(int epoch = 0; epoch < 50; ++epoch) {

    wrap.run_epoch(0.001);
    std::cout<<"#"<<epoch<<"\t";
    wrap.output_epoch_stats();
  }




}
