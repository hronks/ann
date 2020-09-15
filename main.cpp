#include "ann.h"

int main() {

  ANN_wrap <double> wrap ( "housepricedata.csv", 1, 0.7, 10,
                          "networks.dat", DB_BITS*3/4, "output.csv");

  for(int epoch = 0; epoch < 200; ++epoch) {

    wrap.stats.reset_epoch_stats();

    for(int i = 0; i < wrap.data.data_train.size(); ++i) {

      wrap.network.pull_training_data(wrap.data, i);
      wrap.network.run_training(0.01);
      wrap.stats.get_training_stats_binary();
    }

    for(int i = 0; i < wrap.data.data_valid.size(); ++i) {

      wrap.network.pull_validation_data(wrap.data, i);
      wrap.network.predict();
      wrap.stats.get_validation_stats_binary();
    }

    wrap.data.permute_training_data_random();

    wrap.stats.calculate_epoch_stats();
    std::cout<<"#"<<epoch<<"\t";
    wrap.stats.output_epoch_stats();

  }
}
