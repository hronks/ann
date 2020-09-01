#ifndef ANN_H
#define ANN_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "maths.h"

template <class T>
struct Dense_layer {

  std::vector <T> *input;
  std::vector <T> output;
  std::vector <std::vector<T>> weight;
  std::vector <T> bias;
  std::vector <T (*)(T, int)> activation;
  std::vector <std::vector<T>> transpose_weight;
  std::vector <T> d_output;
  std::vector <T> d_bias;
  std::vector <std::vector<T>> d_weight;
  std::vector <T> *pass_back_inbox;
  std::vector <T> pass_back_outbox;

  Dense_layer(int inputs, int outputs, T (*funct)(T, int)) {

//    input.resize(inputs);
    input = NULL;
    pass_back_outbox.resize(inputs);

    output.resize(outputs);
    weight.resize(outputs);
    bias.resize(outputs);
    d_output.resize(outputs);
    d_bias.resize(outputs);
//    pass_back_inbox.resize(outputs);
    pass_back_inbox = NULL;

    weight.resize(outputs);
    for(int i = 0; i < outputs; ++i)
      weight[i].resize(inputs);

    transpose_weight.resize(inputs);
    for(int i = 0; i < inputs; ++i)
      transpose_weight[i].resize(outputs);

    activation.resize(outputs);
    for(int i = 0; i < outputs; ++i)
      activation[i] = funct;

  }

  ~Dense_layer() {
    delete input;
    delete pass_back_inbox;
  }

  void randomize_weights(bool positive) {

    srand((unsigned) time(NULL));

    for(int i =0; i < weight.size(); ++i)
      for(int j = 0; j < weight[i].size(); ++j) {
        weight[i][j] = ((T) rand() / RAND_MAX);
        if(positive == 0) {
          weight[i][j] = (T) (2 * weight[i][j] - 1) / weight[i].size();
        }
        else weight[i][j] /= (T) weight[i].size();
    }

    for(int i =0; i < bias.size(); ++i) {
      bias[i] = ((T) rand() / RAND_MAX);
      if(positive == 0) {
        bias[i] = (T) (2 * bias[i] - 1) / bias.size();
      }
      else bias[i] /= (T) bias.size();
    }


  }

  void link_layers() {

  }

  void forward() {

    // get input
    multiply(weight, *input, output);
    add(bias, output);
    apply(activation, 0, output);
  }

  void backwards() {

    // read back pass inbox
    apply(activation, 1, d_output);
    hadamard(d_output, *pass_back_inbox, d_bias);
    transpose(weight, transpose_weight);
    zeroize(pass_back_outbox);
    multiply(transpose_weight, d_bias, pass_back_outbox);
    outer(d_bias, *input, d_weight);
  }

  void learn(T rate) {

    perturb(d_weight, -rate, weight);
    perturb(d_bias, -rate, bias);
  }

};



#endif
