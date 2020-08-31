#ifndef MATHS_H
#define MATHS_H

#include <iostream>
#include <vector>

template <typename T>
void add( std::vector <std::vector <T>> & operand1,
          std::vector <std::vector <T>> & operand2,
          std::vector <std::vector <T>> & output) {

  for(int i = 0; i < output.size(); ++i)
    for(int j = 0; j < output[i].size(); ++ j) {
      output[i][j] = operand1[i][j] + operand2[i][j];
    }
}

template <typename T>
void add( std::vector <std::vector <T>> & variable,
          std::vector <std::vector <T>> & operand) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++ j) {
      variable[i][j] += operand[i][j];
    }
}

template <typename T>
void multiply(  std::vector <std::vector <T>> & operand1,
                std::vector <std::vector <T>> & operand2,
                std::vector <std::vector <T>> & output) {

  for(int i = 0; i < operand1.size(); ++i)
    for(int j = 0; j < operand2[i].size(); ++ j)
      for(int k = 0; k < operand2.size(); ++k) {
        output[i][j] = operand1[i][k] * operand2[k][j];
      }
  }

template <typename T>
void transpose(std::vector <std::vector <T>> & x) {

  for(int i = 0; i < x.size(); ++i)
    for(int j = 0; j < x[i].size(); ++ j) {
      x[i][j] = -x[i][j];
    }
}



#endif
