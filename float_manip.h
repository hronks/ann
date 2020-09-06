#ifndef FLOAT_MANIP_H
#define FLOAT_MANIP_H

// float:       23  bits long - 6.5 bytes
// double:      52  bits long - 6.5 bytes
// long double  112 bits long - 14 bytes

union u_double
{
    double  d;
    unsigned char data[sizeof(double)];
};

union u_float
{
    float   f;
    unsigned char data[sizeof(float)];
};

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
  ud.data[bits/8] = ud.data[bits/8] >> (bits - ((bits/8)*8));

  d = ud.d;
};

#endif
