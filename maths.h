#ifndef MATHS_H
#define MATHS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

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
void subtract(    const std::vector <T> & operand1,
                  const std::vector <T> & operand2,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] = operand1[i] - operand2[i];
}

template <typename T>
void subtract(    const std::vector <T> & operand,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] -= operand[i];
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

template <typename T>
void hadamard(    const std::vector <T> & operand,
                        std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] *= operand[i];
}

template <typename T>
void hadamard_recip(  const std::vector <T> & operand1,
                      const std::vector <T> & operand2,
                            std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] = operand1[i] / operand2[i];
}

template <typename T>
void hadamard_recip(  const std::vector <T> & operand,
                            std::vector <T> & variable) {

  for(int i = 0; i < variable.size(); ++i)
    variable[i] /= operand[i];
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

template <typename T>
T Sigmoid(T variable, int d) {

  T temp = 1 / (1 + exp(- variable));

  if(d == 0) return temp;
  if(d == 1) return temp*(1-temp);

  return 0;
}

template <typename T>
void Binary_crossentropy( const std::vector <T> & operand,
                          const std::vector <T> & actual,
                                T & error,
                                std::vector <T> & diff) {
  error = 0;

  for(int i = 0; i < diff.size(); ++i)
    diff[i] = (operand[i] - actual[i]) / (operand[i] * (1 - operand[i]));

  for(int i = 0; i < operand.size(); ++i) {
    error -= actual[i] * log(operand[i]) +
      (1 - actual[i]) * log(1 - operand[i]);
  }
  error /= operand.size();
}

/// Combinatorics

std::vector<int> permutation_random(int n) {

  std::vector<int> output;
  std::vector<bool> indicator;
  int r, offset;

  srand((unsigned) time(NULL));
  output.resize(n);
  indicator.resize(n, 1);

  for(int i = 0; i < n; ++i) {
    r = (int) floor(((float) rand()/RAND_MAX)*(n-i));
    offset = 0;
    for(int j = 0; j <= r + offset; ++j) {
      if(indicator[j] == 0) ++offset;
    }
    indicator[r + offset] = 0;
    output[i] = r + offset;
  }
  return output;
}

template <typename T>
void permutation_random(std::vector<std::vector<T>> &data) {

  std::vector<std::vector<T>> temp = data;
  std::vector<int> p;
  p = permutation_random(data.size());

  for(int i = 0; i < data.size(); ++i)
    for(int j = 0; j < data[i].size(); ++j)
      data[i][j] = temp[p[i]][j];
  }

#endif
