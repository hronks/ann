#pragma once

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

void print_bits(const double &d);

void remove_precision(double &d, int bits);
