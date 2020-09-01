#include "ann.h"

int main() {

  std::vector <std::vector <float>> x, y, z;
  std::vector <float> u, v, w;
  std::vector <float (*)(float, int)> f;

  x.push_back({1, -2, 3});
  x.push_back({-4, 5, -6});
  x.push_back({7, -8, 9});

  u = {8450, 7, 5, 856, 2, 1, 3, 8, 0, 548};
  v = {0.232};

  f = {& ReLU <float>, & ReLU <float>, & ReLU <float>};


<<<<<<< HEAD
  Dense_layer <float> l1 (10, 32, & ReLU    <float>);
  Dense_layer <float> l2 (32, 32, & ReLU    <float>);
  Dense_layer <float> l3 (32, 1,  & Sigmoid <float>);
=======
  Dense_layer     <float> l1  (10, 32, & ReLU    <float>);
  Dense_layer     <float> l2  (32, 32, & ReLU    <float>);
  Dense_layer     <float> l3  (32, 1,  & Sigmoid <float>);
  Network_output  <float> out (1, & Binary_crossentropy <float>);
>>>>>>> 3549167268ec60ee53a83e0c3e303d2aaee0455d

  l1.input = & u;
  l1.pass_back_inbox = & l2.pass_back_outbox;
  l1.randomize_weights(0);

  l2.input = & l1.output;
  l2.pass_back_inbox = & l3.pass_back_outbox;
  l2.randomize_weights(0);

  l3.input = & l2.output;
<<<<<<< HEAD
  l3.pass_back_inbox = & v;
  l3.randomize_weights(0);

=======
  l3.pass_back_inbox = & out.d_cost;
  l3.randomize_weights(0);

  out.input = &l3.output;


>>>>>>> 3549167268ec60ee53a83e0c3e303d2aaee0455d

  std::cout<<"\nLAYER 1\n";
  std::cout<<"weight\n"; print(l1.weight);
  std::cout<<"bias\n"; print(l1.bias);

  std::cout<<"\nLAYER 2\n";
  std::cout<<"weight\n"; print(l2.weight);
  std::cout<<"bias\n"; print(l2.bias);

  std::cout<<"\nLAYER 3\n";
  std::cout<<"weight\n"; print(l3.weight);
  std::cout<<"bias\n"; print(l3.bias);



  l1.forward();
  l1.backwards();
  l1.learn(0.000001);


}
