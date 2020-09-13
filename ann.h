#pragma once

#define FL_BITS 23
#define DB_BITS 52
#define LD_BITS 112

#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>

#include "maths.h"
#include "data.h"
#include "float_manip.h"
#include "ann_routines.h"
#include "main_routines.h"

template <class T> struct Layer_hidden;
template <class T> struct Layer_input;
template <class T> struct Layer_output;

template <class T>
struct ANN {

  Layer_input<T>* input_layer;
  Layer_output<T>* output_layer;
  std::vector<Layer_hidden<T>*> hidden_layer;

  ANN() {};

  ANN(std::string file_path) {


  }

  void set_normalization (std::vector<T> offset, std::vector<T> scaling) {

    input_layer->input_offset = offset;
    input_layer->input_scaling = scaling;

  }

  void link() {

    hidden_layer[0]->input = &input_layer->input;

    for(int i = 0; i < hidden_layer.size(); ++i) {
      if(i > 0) hidden_layer[i]->input = &hidden_layer[i-1]->output;
      if(i < hidden_layer.size() - 1)
        hidden_layer[i]->pass_back_inbox = &hidden_layer[i+1]->pass_back_outbox;
    }
    hidden_layer[hidden_layer.size()-1]->pass_back_inbox =
      &output_layer->d_cost;

    output_layer->input = &hidden_layer[hidden_layer.size()-1]->output;
    output_layer->actual = &input_layer->output;

  }

  void randomize_weights(bool positive) {
    for(int i = 0; i < hidden_layer.size(); ++i)
      hidden_layer[i]->randomize_weights(positive);
  };

  void pull_training_data(ANN_data <T> & data, int row) {

    input_layer->raw_input  =
      Pull_data <T> (data.data_train, row, 1, data.xy_crossover);
    input_layer->raw_output =
      Pull_data <T> (data.data_train, row, data.xy_crossover + 1, data.columns);
  };

  void normalize() {
    input_layer->normalize();
  };

  void remove_precision(int bits) {
    input_layer->remove_precision_li(bits);
  };

  void forward() {
    for(int i = 0; i < hidden_layer.size(); ++i) {
      hidden_layer[i]->forward();
    }
    output_layer->calculate();
  };

  void backwards() {
    for(int i = hidden_layer.size() - 1; i >= 0; --i)
      hidden_layer[i]->backwards();
  };

  void learn(float h) {
    for(int i = 0; i < hidden_layer.size(); ++i) {
      hidden_layer[i]->learn(h);
    }
  };

  void run_epoch(int remove_start_precision_bits, float h) {

    normalize();
    remove_precision(remove_start_precision_bits);
    forward();
    backwards();
    learn(h);
    forward();
  };

  void predict(int remove_start_precision_bits) {

    normalize();
    remove_precision(remove_start_precision_bits);
    forward();
  }


};

template<class T>
struct Layer_hidden {

  std::vector <T> *input;
  std::vector <T> output;
  std::vector <T> *pass_back_inbox;
  std::vector <T> pass_back_outbox;

  virtual void randomize_weights(bool positive)   {return;}
  virtual void forward()                          {return;}
  virtual void backwards()                        {return;}
  virtual void learn(float h)                     {return;}
};

template<class T>
struct Layer_input {

  std::vector <T> input;
  std::vector <T> output;

  std::vector<T> raw_input;
  std::vector<T> raw_output;

  std::vector<T> input_offset;
  std::vector<T> input_scaling;

  std::vector<T> output_offset;
  std::vector<T> output_scaling;

  virtual void normalize()                        {return;}
  virtual void remove_precision_li(int bits)      {return;}

};

template<class T>
struct Layer_output {

  std::vector <T> *input;
  std::vector <T> *actual;
  std::vector <T> d_cost;
  T cost;

  virtual void calculate()                        {return;}

};

template <class T>
struct Dense_layer: public Layer_hidden<T> {

  std::vector <std::vector<T>> weight;
  std::vector <T> bias;
  std::vector <T (*)(T, int)> activation;

  std::vector <std::vector<T>> transpose_weight;
  std::vector <T> d_output;
  std::vector <T> d_bias;
  std::vector <std::vector<T>> d_weight;

  Dense_layer(int inputs, int outputs, T (*funct)(T, int)) {

    Layer_hidden<T>::input = NULL;
    Layer_hidden<T>::pass_back_outbox.resize(inputs);

    Layer_hidden<T>::output.resize(outputs);
    weight.resize(outputs);
    bias.resize(outputs);
    d_output.resize(outputs);
    d_bias.resize(outputs);
    Layer_hidden<T>::pass_back_inbox = NULL;

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

  void forward() {

    multiply(weight, *Layer_hidden<T>::input, Layer_hidden<T>::output);
    add(bias, Layer_hidden<T>::output);
    d_output = Layer_hidden<T>::output;
    apply(activation, 0, Layer_hidden<T>::output);

  }

  void backwards() {
    apply(activation, 1, d_output);
    hadamard(d_output, *Layer_hidden<T>::pass_back_inbox, d_bias);
    transpose(weight, transpose_weight);
    zeroize(Layer_hidden<T>::pass_back_outbox);
    multiply(transpose_weight, d_bias, Layer_hidden<T>::pass_back_outbox);
    outer(d_bias, *Layer_hidden<T>::input, d_weight);
  }

  void learn(float rate) {

    T rate_T;
    rate_T = rate;
    perturb(d_weight, -rate_T, weight);
    perturb(d_bias, -rate_T, bias);
  }

};

template <class T>
struct Network_output: public Layer_output<T> {

  void (* cost_function)( const std::vector <T> &,
                          const std::vector <T> &,
                          T & error,
                          std::vector <T> & diff );

  Network_output(int inputs, void (*funct)( const std::vector <T> &,
                                            const std::vector <T> &,
                                            T & error,
                                            std::vector <T> &)) {

      Layer_output<T>::input = NULL;
      Layer_output<T>::actual = NULL;
      cost_function = funct;
      Layer_output<T>::d_cost.resize(inputs);
  }

  ~Network_output() {}

  void calculate() {

    cost_function(*Layer_output<T>::input, *Layer_output<T>::actual, Layer_output<T>::cost, Layer_output<T>::d_cost);
  }
};

template <class T>
struct Network_input: public Layer_input<T> {

  Network_input(int inputs, int outputs) {

    Layer_input<T>::raw_input.resize(inputs, 0);
    Layer_input<T>::raw_output.resize(outputs, 0);
    Layer_input<T>::input_offset.resize(inputs, 0);
    Layer_input<T>::input_scaling.resize(inputs, 1);
    Layer_input<T>::output_offset.resize(outputs, 0);
    Layer_input<T>::output_scaling.resize(outputs, 1);
    Layer_input<T>::input.resize(inputs);
    Layer_input<T>::output.resize(outputs);
  }

  ~Network_input() {}

  void normalize() {

    subtract(Layer_input<T>::raw_input,  Layer_input<T>::input_offset,  Layer_input<T>::input);
    hadamard_recip(Layer_input<T>::input_scaling,  Layer_input<T>::input);

    subtract(Layer_input<T>::raw_output, Layer_input<T>::output_offset, Layer_input<T>::output);
    hadamard_recip(Layer_input<T>::output_scaling, Layer_input<T>::output);

    for(int i = 0; i < Layer_input<T>::input.size(); ++i) {
      Layer_input<T>::input[i] = (float) Layer_input<T>::input[i];
    }

  }

  void remove_precision_li(int bits) {
    for(int i = 0; i < Layer_input<T>::input.size(); ++i)
      remove_precision(Layer_input<T>::input[i], bits);
  }

};
