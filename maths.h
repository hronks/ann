#ifndef MATHS_H
#define MATHS_H

#include <iostream>
#include <vector>


/// Matrices functions

template <typename T>
void print(       const std::vector <std::vector <T>> & operand) {

  for(int i = 0; i < operand.size(); ++i) {
    std::cout<<"{";
    for(int j = 0; j < operand[i].size(); ++j) {
      std::cout<<operand[i][j];
      if(j < operand[i].size() - 1) std::cout<<", ";
    }
    std::cout<<"}\n";
  }
}

template <typename T>
void add(         const std::vector <std::vector <T>> & operand1,
                  const std::vector <std::vector <T>> & operand2,
                        std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++ j) {
      variable[i][j] = operand1[i][j] + operand2[i][j];
    }
}

template <typename T>
void add(         const std::vector <std::vector <T>> & operand,
                        std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++ j) {
      variable[i][j] += operand[i][j];
    }
}

template <typename T>
void multiply(    const std::vector <std::vector <T>> & operand1,
                  const std::vector <std::vector <T>> & operand2,
                        std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++ j)
      variable[i][j] = 0;

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++ j)
      for(int k = 0; k < operand2.size(); ++k) {
        variable[i][j] += operand1[i][k] * operand2[k][j];
      }
  }

template <typename T>
void transpose(   const std::vector <std::vector <T>> & operand,
                        std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++ j)
      variable[i][j] = operand[j][i];
}



#endif
