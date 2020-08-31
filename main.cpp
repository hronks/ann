#include "ann.h"

int main() {

  std::vector <std::vector <float>> x, y, z;
  std::vector <float> u, v, w;
  std::vector <float (*)(float, int)> f;

  x.push_back({1, -2, 3});
  x.push_back({-4, 5, -6});
  x.push_back({7, -8, 9});
  u = {-1, 2, -3};
  v = {4, -5, 6};
  w = {-7, 8, -9};
  f = {& ReLU <float>, & ReLU <float>, & ReLU <float>};

  Dense_layer <float> l (3, 3, & ReLU <float>);
  
  l.input = u;
  l.weight = x;
  l.bias = w;
  l.activation = f;
  l.output = v;

  l.d_output = v;
  l.transpose_weight = x;

  l.pass_back_inbox = v;
  l.pass_back_outbox = v;

  l.d_weight = x;
  l.d_bias = v;

  print(l.input);
  print(l.weight);
  print(l.bias);

  l.forward();
  l.backwards();
  l.learn(0.000001);


}
