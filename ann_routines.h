#pragma once

#include "ann.h"

struct Layer_hidden;
struct Layer_input;
struct Layer_output;

struct Layer_hidden {

  Layer_input * input_i;
  Layer_hidden* input_h;

  Layer_hidden* output_h;
  Layer_output* output_o;

  virtual void randomize_weights(bool positive)   {return;}
  virtual void forward()                          {return;}
  virtual void backwards()                        {return;}
  virtual void learn(float h)                     {return;}

  void link(Layer_input* in, Layer_hidden* out) {
    input_i = in;
    output_h = out;
  }

  void link(Layer_hidden* in, Layer_hidden* out) {
    input_h = in;
    output_h = out;
  }

  void link(Layer_hidden* in, Layer_output* out) {
    input_h = in;
    output_o = out;
  }

  void link(Layer_input* in, Layer_output* out) {
    input_i = in;
    output_o = out;
  }
};

struct Layer_input {

  virtual void normalize()                        {return;}
  virtual void remove_precision_li(int bits)      {return;}

};

struct Layer_output {

  virtual void calculate()                        {return;}

};

struct ANN {

  Layer_input* input_layer;
  Layer_output* output_layer;
  std::vector<Layer_hidden*> hidden_layer;

  void randomize_weights(bool positive) {
    for(int i = 0; i < hidden_layer.size(); ++i)
      hidden_layer[i]->randomize_weights(positive);
  };

  void link() {

    output_layer->link()




  }

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
