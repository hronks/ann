#pragma once

template <class T>
struct ANN_stats {

  ANN <T> * network;

  T epoch_average_train_cost;
  int successful_train_trials;
  int total_train_trials;
  T epoch_train_accuracy;

  T epoch_average_valid_cost;
  int successful_valid_trials;
  int total_valid_trials;
  T epoch_valid_accuracy;

  std::string output_path;


//  std::ofstream graph_stream("output.csv");

  ANN_stats () {
    network = NULL;
  };

  ANN_stats(ANN <T> & set_network, ANN_data <T> & data, std::string path_name) {

    network = & set_network;

    total_train_trials = data.data_train.size();
    total_valid_trials = data.data_valid.size();

  }

  void reset_epoch_stats() {

    epoch_average_train_cost = 0;
    successful_train_trials = 0;
    epoch_train_accuracy = 0;

    epoch_average_valid_cost = 0;
    successful_valid_trials = 0;
    epoch_valid_accuracy = 0;

  }

  void get_training_stats_binary() {

    T correct = 1;

    for(int i = 0; i < (*network->output_layer->input).size(); ++i) {
      if( (*network->output_layer->input)[0] - (*network->output_layer->actual)[0] >  0.5 ||
        (*network->output_layer->input)[0] - (*network->output_layer->actual)[0] < -0.5) {

        correct = 0;
        break;
      }
    }
    epoch_train_accuracy += correct;
    epoch_average_train_cost += network->output_layer->cost;
  }

  void get_validation_stats_binary() {

    T correct = 1;

    for(int i = 0; i < (*network->output_layer->input).size(); ++i) {
      if( (*network->output_layer->input)[0] - (*network->output_layer->actual)[0] >  0.5 ||
        (*network->output_layer->input)[0] - (*network->output_layer->actual)[0] < -0.5) {

        correct = 0;
        break;
      }
    }
    epoch_valid_accuracy += correct;
    epoch_average_valid_cost += network->output_layer->cost;

  }

  void calculate_epoch_stats() {

    epoch_train_accuracy /= (float) total_train_trials;
    epoch_average_train_cost /= (float) total_train_trials;

    epoch_valid_accuracy /= (float) total_valid_trials;
    epoch_average_valid_cost /= (float) total_valid_trials;

  }

  void output_epoch_stats() {

    std::ofstream out_stream(output_path);

    std::cout<<epoch_average_train_cost<<", "<<epoch_train_accuracy<<"\t";
    std::cout<<epoch_average_valid_cost<<", "<<epoch_valid_accuracy<<"\n";

    out_stream<<epoch_average_train_cost<<","<<epoch_train_accuracy<<",";
    out_stream<<epoch_average_valid_cost<<","<<epoch_valid_accuracy<<"\n";

  }

};
