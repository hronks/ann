#include "ann.h"

#define FL_BITS 23
#define DB_BITS 52
#define LD_BITS 112

int main() {

  // load data and divide bwtween training and validation

  int rows, columns;
  std::vector<std::vector<double>> data, data_train, data_valid;
  CSV_scan <double> ("housepricedata.csv", 1, rows, columns);
  CSV_load <double> ("housepricedata.csv", 1, rows, columns, data);

  Random_split <double> (data, 0.7, data_train, data_valid);

  // create the layers and randomize weights

  std::vector <double> x, y;

  Network_input  <double> in  (10, 1);
  Dense_layer    <double> l1  (10, 32, & ReLU    <double>);
  Dense_layer    <double> l2  (32, 32, & ReLU    <double>);
  Dense_layer    <double> l3  (32, 1,  & Sigmoid <double>);
  Network_output <double> out (1, & Binary_crossentropy <double>);

  l1.randomize_weights(0);
  l2.randomize_weights(0);
  l3.randomize_weights(0);

  // set the normalization data

  in.input_offset   = Sample_mean <double> (data, 1, 10);
  in.input_scaling  = Sample_sd   <double> (data, in.input_offset, 1, 10);
  in.output_offset  = {0};
  in.output_scaling = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  // create the network wrapper and link the layers

  ANN network(3);

  network.l[0] = &in;
  network.l[1] = &l1;
  network.l[2] = &l2;
  network.l[3] = &l3;
  network.l[4] = &out;

  network.link();

  in.raw_input = & x;
  in.raw_output = & y;
  l1.input = & in.input;
  l1.pass_back_inbox = & l2.pass_back_outbox;
  l2.input = & l1.output;
  l2.pass_back_inbox = & l3.pass_back_outbox;
  l3.input = & l2.output;
  l3.pass_back_inbox = & out.d_cost;
  out.input = &l3.output;
  out.actual = & in.output;

  // create observables for training and validation

  float epoch_average_train_cost = 0;
  float epoch_train_accuracy = 0;
  float epoch_average_valid_cost = 0;
  float epoch_valid_accuracy = 0;
  int error_code = 0;

  std::cout<<"\n";

  // run through epochs

  for(int epoch = 0; epoch < 1; ++epoch) {

    // train the network

    for(int i = 0; i < data_train.size(); ++i) {

      // initiate data and pass forward

      float old_cost;

      x = Pull_data <double> (data_train, i,  1, 10);
      y = Pull_data <double> (data_train, i, 11, 11);

      in.normalize();

      for(int i = 0; i < in.input.size(); ++i)
        remove_precision(in.input[i], (DB_BITS*3)/4);

      l1.forward();
      l2.forward();
      l3.forward();

      out.calculate();
      old_cost = out.cost;

      if(isinf(out.cost) || isnan(out.cost)) {
        error_code = 1;
        goto stop;
      }

      // calulate derviatives, improve and recalculate output

      l3.backwards();
      l2.backwards();
      l1.backwards();

      l1.learn(0.01);
      l2.learn(0.01);
      l3.learn(0.01);

      l1.forward();
      l2.forward();
      l3.forward();

      out.calculate();

      // update training epoch statistics

//    std::cout<<"#"<<i<<"\t"<<old_cost<<"\t->  "<<out.cost<<"\n";

      if( (*out.input)[0] - (*out.actual)[0] <  0.5 &&
          (*out.input)[0] - (*out.actual)[0] > -0.5) epoch_train_accuracy += (double) 1;
      epoch_average_train_cost += out.cost;
    }


    // calulcate validation error

    for(int i = 0; i < data_valid.size(); ++i) {

      x = Pull_data <double> (data_valid, i,  1, 10);
      y = Pull_data <double> (data_valid, i, 11, 11);

      in.normalize();

      l1.forward();
      l2.forward();
      l3.forward();

      out.calculate();

      // update validation epoch statistics

      if( (*out.input)[0] - (*out.actual)[0] <  0.5 &&
          (*out.input)[0] - (*out.actual)[0] > -0.5) epoch_valid_accuracy += (float) 1;
      epoch_average_valid_cost += out.cost;
    }


    // permute the training data

    permutation_random <double> (data_train);

    // epoch statistics

    epoch_train_accuracy /= (double) data_train.size();
    epoch_average_train_cost /= data_train.size();

    epoch_valid_accuracy /= (double) data_valid.size();
    epoch_average_valid_cost /= data_valid.size();

    std::cout<<"#"<<epoch<<"\t"<<epoch_average_train_cost<<", "<<epoch_train_accuracy<<"\t";
    std::cout<<epoch_average_valid_cost<<", "<<epoch_valid_accuracy<<"\n";

  }

  stop:
    if(error_code == 1) std::cout<<"COST FUNCTION LIMIT ERROR";
}
