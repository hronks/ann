#ifndef ANN_H
#define ANN_H

#include <iostream>
#include <vector>
#include <ctime>

#include "maths.h"
#include "data.h"

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

    input = NULL;
    pass_back_outbox.resize(inputs);

    output.resize(outputs);
    weight.resize(outputs);
    bias.resize(outputs);
    d_output.resize(outputs);
    d_bias.resize(outputs);
    pass_back_inbox = NULL;

    weight.resize(outputs);
    for(int i = 0; i < outputs; ++i)
      weight[i].resize(inputs);

    d_weight.resize(outputs);
    for(int i = 0; i < outputs; ++i)
      d_weight[i].resize(inputs);

    transpose_weight.resize(inputs);
    for(int i = 0; i < inputs; ++i)
      transpose_weight[i].resize(outputs);

    activation.resize(outputs);
    for(int i = 0; i < outputs; ++i)
      activation[i] = funct;

  }

  ~Dense_layer() {}

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

    multiply(weight, *input, output);
    add(bias, output);
    d_output = output;
    apply(activation, 0, output);
  }

  void backwards() {
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

template <class T>
struct Network_output {

  std::vector <T> *input;
  std::vector <T> *actual;
  T cost;
  void (* cost_function)( const std::vector <T> &,
                          const std::vector <T> &,
                          T & error,
                          std::vector <T> & diff );
  std::vector <T> d_cost;

  Network_output(int inputs, void (*funct)( const std::vector <T> &,
                                            const std::vector <T> &,
                                            T & error,
                                            std::vector <T> &)) {

      input = NULL;
      actual = NULL;
      cost_function = funct;
      d_cost.resize(inputs);
  }

  ~Network_output() {}

  void calculate() {

    cost_function(*input, *actual, cost, d_cost);
  }
};

template <class T>
struct Network_input {

  std::vector<T>* raw_input;
  std::vector<T>* raw_output;

  std::vector<T> input_offset;
  std::vector<T> input_scaling;
  std::vector<T> output_offset;
  std::vector<T> output_scaling;

  std::vector<T> input;
  std::vector<T> output;

  Network_input(int inputs, int outputs) {

    raw_input = NULL;
    raw_output = NULL;
    input_offset.resize(inputs, 0);
    input_scaling.resize(inputs, 1);
    output_offset.resize(outputs, 0);
    output_scaling.resize(outputs, 1);
    input.resize(inputs);
    output.resize(outputs);
  }

  ~Network_input() {}

  void normalize() {

    subtract(*raw_input,  input_offset,  input);
    hadamard_recip(input_scaling,  input);

    subtract(*raw_output, output_offset, output);
    hadamard_recip(output_scaling, output);
  }

};

#endif
