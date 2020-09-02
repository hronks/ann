#include "ann.h"

int main() {

  // load data

  int rows, columns;
  std::vector<std::vector<float>> data;
  CSV_scan <float> ("housepricedata.csv", 1, rows, columns);
  CSV_load <float> ("housepricedata.csv", 1, rows, columns, data);

  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < columns; ++j) {
      std::cout<<data[i][j]<<" ";
    }
    std::cout<<"\n";
  }

  // create and link the network

  std::vector <float> x, y;

  Network_input  <float> in  (10, 1);
  Dense_layer    <float> l1  (10, 32, & ReLU    <float>);
  Dense_layer    <float> l2  (32, 32, & ReLU    <float>);
  Dense_layer    <float> l3  (32, 1,  & Sigmoid <float>);
  Network_output <float> out (1, & Binary_crossentropy <float>);

  l1.randomize_weights(0);
  l2.randomize_weights(0);
  l3.randomize_weights(0);

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

  // initiate data and calculate initital cost

  x = {8450, 7, 5, 856, 2, 1, 3, 8, 0, 548};
  y = {1};
  in.rescale();

  l1.forward();
  l2.forward();
  l3.forward();
  out.calculate();
  std::cout<<out.cost<<"\n";

  // calulate improved cost

  for(int i = 0; i < 10; ++i) {
    l3.backwards();
    l2.backwards();
    l1.backwards();
    l1.learn(0.00001);
    l2.learn(0.00001);
    l3.learn(0.00001);
    l1.forward();
    l2.forward();
    l3.forward();
    out.calculate();
    std::cout<<out.cost<<"\n";
  }

}
