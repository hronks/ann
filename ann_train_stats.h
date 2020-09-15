#pragma once

template <class T>
struct ANN_stats {

  ANN <T> * network;

  T epoch_average_train_cost;
  int successful_train_trails;
  int total_train_trails;
  T epoch_train_accuracy;

  T epoch_average_valid_cost;
  int successful_valid_trails;
  int total_valid_trails;
  T epoch_valid_accuracy;

  std::string output_path;

//  std::ofstream graph_stream("output.csv");

  void reset_epoch_stats() {

  }

  void get_epoch_train_stats() {

  }

  void get_epoch_valid_stats() {

  }




};
