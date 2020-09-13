#include "ann.h"

int main() {

  ANN_data <double> data("housepricedata.csv", 1, 0.7, 10);

  ANN <double> network2("networks.dat");

  //std::cout<<network2->input_layer.size();


  // ANN network   =  load_network("network1.dat", 1);
  // ANN_training_output output; [output vectors for graphing]
  // netwok.train(ANN_data, 100, ANN_output, 1 [bool - show output live]);
  // output.something(); [some summary information from training]

  Network_input  <double> in  (10, 1);
  Dense_layer    <double> l1  (10, 32, & ReLU    <double>);
  Dense_layer    <double> l2  (32, 32, & ReLU    <double>);
  Dense_layer    <double> l3  (32, 1,  & Sigmoid <double>);
  Network_output <double> out (1, & Binary_crossentropy <double>);

  // create the network, normalize, link and randomize_weights

  ANN <double> network;
  network.input_layer  = &in;
  network.hidden_layer = {&l1, &l2, &l3};
  network.output_layer = &out;
  network.link();
  network.randomize_weights(0);

  network.set_normalization(Sample_mean <double> (data.data, 1, 10),
                      Sample_sd <double> (data.data, in.input_offset, 1, 10));

  // create observables for training and validation

  float epoch_average_train_cost = 0;
  float epoch_train_accuracy = 0;
  float epoch_average_valid_cost = 0;
  float epoch_valid_accuracy = 0;
  std::ofstream graph_stream("output.csv");

  // run through epochs

  for(int epoch = 0; epoch < 1; ++epoch) {

    // train the network

    for(int i = 0; i < data.data_train.size(); ++i) {

      // initiate data and pass forward

      network.pull_training_data(data, i);

//      network.input_layer->raw_input  = Pull_data <double> (data.data_train, i,  1, 10);
//      network.input_layer->raw_output = Pull_data <double> (data.data_train, i, 11, 11);

      network.run_epoch((DB_BITS*3)/4, 0.01);


      if( (*network.output_layer->input)[0] - (*network.output_layer->actual)[0] <  0.5 &&
          (*network.output_layer->input)[0] - (*network.output_layer->actual)[0] > -0.5) epoch_train_accuracy += (double) 1;
      epoch_average_train_cost += network.output_layer->cost;
    }



    // calulcate validation error

    for(int i = 0; i < data.data_valid.size(); ++i) {

      network.input_layer->raw_input  = Pull_data <double> (data.data_valid, i,  1, 10);
      network.input_layer->raw_output = Pull_data <double> (data.data_valid, i, 11, 11);
      network.predict((DB_BITS*3)/4);

      // update validation epoch statistics

      if( (*network.output_layer->input)[0] - (*network.output_layer->actual)[0] <  0.5 &&
          (*network.output_layer->input)[0] - (*network.output_layer->actual)[0] > -0.5) epoch_valid_accuracy += (float) 1;
      epoch_average_valid_cost += network.output_layer->cost;
    }

    // permute the training data

    permutation_random <double> (data.data_train);

    // epoch statistics

    epoch_train_accuracy /= (double) data.data_train.size();
    epoch_average_train_cost /= data.data_train.size();

    epoch_valid_accuracy /= (double) data.data_valid.size();
    epoch_average_valid_cost /= data.data_valid.size();

    std::cout<<"#"<<epoch<<"\t"<<epoch_average_train_cost<<", "<<epoch_train_accuracy<<"\t";
    std::cout<<epoch_average_valid_cost<<", "<<epoch_valid_accuracy<<"\n";

    graph_stream<<epoch<<","<<epoch_average_train_cost<<","<<epoch_train_accuracy<<",";
    graph_stream<<epoch_average_valid_cost<<","<<epoch_valid_accuracy<<"\n";

  }

}
