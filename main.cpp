#include "ann.h"

int main() {

  std::vector <std::vector <float>> x, y, z;

  x.push_back({1, 2, 3});
  x.push_back({4, 5, 6});
  x.push_back({7, 8, 9});

  y.push_back({1, 2, 3});
  y.push_back({4, 5, 6});
  y.push_back({7, 8, 9});

  z.push_back({0, 0, 0});
  z.push_back({0, 0, 0});
  z.push_back({0, 0, 0});

  add <float> (x, y, z);

  print(x);
  print(y);
  print(z);





}
