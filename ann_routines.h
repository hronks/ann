#pragma once

#include "ann.h"

struct ANN {

  Layer_input* input_layer;
  Layer_output* output_layer;
  std::vector<Layer_hidden*> hidden_layer;

  ANN() {};
  ANN(std::string file_path);

  void randomize_weights(bool positive) {
    for(int i = 0; i < hidden_layer.size(); ++i)
      hidden_layer[i]->randomize_weights(positive);
  };

  void normalize() {
    input_layer->normalize();
  };

  void remove_precision(int bits) {
    input_layer->remove_precision_li(bits);
  };

  void forward() {
    for(int i = 0; i < hidden_layer.size(); ++i)
      hidden_layer[i]->forward();
    output_layer->calculate();
  };

  void backwards() {
    for(int i = hidden_layer.size() - 1; i >= 0; --i)
      hidden_layer[i]->backwards();
  };

  void learn(float h) {
    for(int i = 0; i < hidden_layer.size(); ++i)
      hidden_layer[i]->learn(h);
  };

  void run_epoch(int remove_start_precision_bits, float h) {

    normalize();
    remove_precision(remove_start_precision_bits);
    forward();
    backwards();
    learn(h);
    forward();
  };

  void predict() {

    normalize();
    forward();
  }
};
