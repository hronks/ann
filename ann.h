#ifndef ANN_H
#define ANN_H

#include <iostream>
#include <vector>

#include "maths.h"

template <class T>
struct Dense_layer {

  std::vector <T> input;
  std::vector <T> output;

  std::vector <std::vector<T>> weight;
  std::vector <T> bias;
  std::vector <T (*)(T, int)> activation;

  std::vector <std::vector<T>> transpose_weight;
  std::vector <T> d_output;

  std::vector <T> d_bias;
  std::vector <std::vector<T>> d_weight;

  std::vector <T> pass_back_inbox;
  std::vector <T> pass_back_outbox;

  Dense_layer(int inputs, int outputs, T (*)(T, int)) {

  }

  void randomize_weights() {

  }

  void link_layers() {

  }

  void forward() {

    // get input
    multiply(weight, input, output);
    add(bias, output);
    apply(activation, 0, output);
  }

  void backwards() {

    // read back pass inbox
    apply(activation, 1, d_output);
    hadamard(d_output, pass_back_inbox, d_bias);
    transpose(weight, transpose_weight);
    zeroize(pass_back_outbox);
    multiply(transpose_weight, d_bias, pass_back_outbox);
    outer(d_bias, input, d_weight);
  }

  void learn(T rate) {

    perturb(d_weight, -rate, weight);
    perturb(d_bias, -rate, bias);
  }

};

#endif
