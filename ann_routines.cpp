#include "ann.h"

ANN::ANN(std::string file_path) {

  std::ifstream file_in(file_path);

  std::string line, line2;
  std::string type;
  int integer, integer2;

  file_in >> line; file_in >> integer;
  std::cout << integer <<"\n";

  file_in >> line; file_in >> line;
  std::cout<<line<<"\n";

  file_in >> line; file_in >> line;
  std::cout << line <<"\n";

  file_in >> line; file_in >> line;
  std::cout << line <<"\n";

  file_in >> line; file_in >> integer;
  std::cout << integer <<"\n";

  file_in >> line; file_in >> integer;
  std::cout << integer <<"\n";

  file_in >> line; file_in >> integer;
  hidden_layer.resize(integer);
  std::cout << hidden_layer.size() <<"\n";

  for(int i = 0; i < hidden_layer.size(); ++i) {

    file_in >> line; file_in >> line;
    std::cout << line <<"\n";

    file_in >> line; file_in >> integer;
    std::cout << integer <<"\n";

    file_in >> line; file_in >> integer2;
    std::cout << integer <<"\n";

    file_in >> line; file_in >> line2;
    std::cout << line <<"\n";

    if( line == "Dense_layer_<double>" &&
        line2== "ReLU_<double>") {
      Dense_layer<double>  temp (integer, integer2, & ReLU<double>);
      hidden_layer[i] = new Dense_layer<double> (integer, integer2, & ReLU<double>);
      hidden_layer[i] = & temp;
    }

    if( line == "Dense_layer_<double>" &&
        line2== "Sigmoid_<double>") {
      Dense_layer<double> l1 (integer, integer2, & Sigmoid<double>);
    }

  }

  file_in >> line; file_in >> line;
  std::cout<<line<<"\n";

  file_in >> line; file_in >> line;
  std::cout<<line<<"\n";

  file_in >> line; file_in >> integer;
  std::cout<<integer<<"\n";

  file_in >> line; file_in >> line;
  std::cout<<line<<"\n";

  file_in >> line; file_in >> integer;
  std::cout<<integer<<"\n";

}
