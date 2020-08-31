#ifndef MATHS_H
#define MATHS_H

#include <iostream>
#include <vector>

/// Vector functions

template <typename T>
void zeroize(           std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] = 0;
}

template <typename T>
void print(       const std::vector <T> & operand) {

  std::cout<<"<";
  for(int i = 0; i < operand.size(); ++i) {
    std::cout<<operand[i];
    if(i < operand.size() - 1) std::cout<<", ";
  }
  std::cout<<">\n";
}

template <typename T>
void add(         const std::vector <T> & operand1,
                  const std::vector <T> & operand2,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] = operand1[i] + operand2[i];
}

template <typename T>
void add(         const std::vector <T> & operand,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] += operand[i];
}

template <typename T>
void perturb(     const std::vector <T> & operand,
                        T adjustment,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] += adjustment * operand[i];
}

template <typename T>
void dot(         const std::vector <T> & operand1,
                  const std::vector <T> & operand2,
                        T & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable += operand1[i]*operand2[i];
}

template <typename T>
void hadamard(    const std::vector <T> & operand1,
                  const std::vector <T> & operand2,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] = operand1[i] * operand2[i];
  }

/// Matrix functions

template <typename T>
void zeroize(           std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++j)
      variable[i][j] = 0;
}

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
void perturb(     const std::vector <std::vector <T>> & operand,
                        T adjustment,
                        std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++j)
      variable[i][j] += adjustment * operand[i][j];
}

template <typename T>
void multiply(    const std::vector <std::vector <T>> & operand1,
                  const std::vector <std::vector <T>> & operand2,
                        std::vector <std::vector <T>> & variable) {

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

template <typename T>
void hadamard(    const std::vector <std::vector <T>> & operand1,
                  const std::vector <std::vector <T>> & operand2,
                        std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++ j)
        variable[i][j] = operand1[i][j] * operand2[i][j];
  }

/// Matrix-vector functions

template <typename T>
void multiply(    const std::vector <std::vector <T>> & operand1,
                  const std::vector <T> & operand2,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] = 0;

  for(int i = 0; i < variable.size(); ++i)
    for(int k = 0; k < operand2.size(); ++k)
      variable[i] += operand1[i][k] * operand2[k];
  }

template <typename T>
void outer(       const std::vector <T> & operand1,
                  const std::vector <T> & operand2,
                        std::vector <std::vector <T>> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    for(int j = 0; j < variable[i].size(); ++j)
      variable[i][j] = operand1[i] * operand2[j];
}

/// Multivariable functions

template <typename T>
void apply( std::vector <T (*)(T, int)> funct, int d,
            std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] = funct[i](variable[i], d);

}

/// Mathematical functions

template <typename T>
T ReLU(T variable, int d) {

  if(d == 0) {
    if(variable > 0) return variable;
    else return 0;
  }

  if(d == 1) {
    if(variable > 0) return 1;
    else return 0;
  }

  return 0;
}




#endif
