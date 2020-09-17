#include <vector>
#include <ctime>
#include "math.h"

std::vector<int> permutation_random(int n) {

  std::vector<int> output;
  std::vector<bool> indicator;
  int r, offset;

  srand((unsigned) time(NULL));
  output.resize(n);
  indicator.resize(n, 1);

  for(int i = 0; i < n; ++i) {
    r = (int) floor(((float) rand()/(RAND_MAX+1))*(n-i));
    offset = 0;
    for(int j = 0; j <= r + offset; ++j) {
      if(indicator[j] == 0) ++offset;
    }
    indicator[r + offset] = 0;
    output[i] = r + offset;
  }
  return output;
}
