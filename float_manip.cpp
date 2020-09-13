#include "float_manip.h"
#include <iostream>

void print_bits(const double &d) {

  u_double ud;
  ud.d = d;
  unsigned char temp;

  for(int i = 0; i < 6; ++i) {
    temp = ud.data[i];
    for(int j = 0; j < 8; ++j) {
      std::cout<<temp%2<<" ";
      temp /= 2;
    }
  }
  temp = ud.data[6];
  for(int j = 0; j < 4; ++j) {
    std::cout<<temp%2<<" ";
    temp /= 2;
  }
}

void remove_precision(double &d, int bits) {

  u_double ud;
  ud.d = d;

  for(int i = 0; i < bits/8; ++i)
    ud.data[i] = 0;
  for(int i = 0; i < bits - ((bits/8)*8); ++i)
    ud.data[bits/8] /= 2;

//  ud.data[bits/8] = ud.data[bits/8] << (bits - ((bits/8)*8));

  d = ud.d;
};
