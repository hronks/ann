#pragma once

#include <string>
#include <fstream>
#include "maths.h"

// CSV operations

template <typename T>
void CSV_scan ( const std::string path_name, const bool has_header,
                int & rows, int & columns) {

  std::string line;
  std::ifstream file_stream(path_name);
  rows = -1;

  if(has_header == 1) file_stream >> line;

  while(!file_stream.eof()) {
    ++rows;
    file_stream >> line;
    if(rows == 0) {
      columns = 1;
      for(int i = 0; i < line.length(); ++i) {
        if(line[i] == ',') ++columns;
      }
    }
  }
  file_stream.close();
}

template <typename T>
void CSV_load ( const std::string path_name, const bool has_header,
                const int rows, const int columns,
                std::vector<std::vector<T>> & data) {

  std::string line;
  char temp;
  std::ifstream file_stream(path_name);
  if(has_header == 1) file_stream >> line;

  data.resize(rows);
  for(int i = 0; i < rows; ++i) data[i].resize(columns + 1);

  for(int i = 0; i < rows; ++i) {
    data[i][0] = i;
    for(int j = 1; j <= columns; ++j) {
      file_stream >> data[i][j];
      if(j < columns ) file_stream >> temp;
    }
  }
}

// Manipulating data

template <typename T>
void Random_split ( const std::vector<std::vector<T>> & raw_data, float proportion,
                          std::vector<std::vector<T>> & data_1,
                          std::vector<std::vector<T>> & data_2) {

  int last_row = (int) floor( proportion * raw_data.size());
  std::vector<int> p;
  p = permutation_random(raw_data.size());

  data_1.resize(last_row);
  for(int i = 0; i < last_row; ++i)
    data_1[i].resize(raw_data[i].size());

  data_2.resize(raw_data.size() - last_row);
  for(int i = last_row; i < raw_data.size(); ++i)
    data_2[i - last_row].resize(raw_data[i].size());

  for(int i = 0; i < last_row; ++i)
    for(int j = 0; j < raw_data[i].size(); ++j)
      data_1[i][j] = raw_data[ p[i] ][j];

  for(int i = last_row; i < raw_data.size(); ++i)
    for(int j = 0; j < raw_data[i].size(); ++j)
      data_2[i - last_row][j] = raw_data[ p[i] ][j];

}

template <typename T>
std::vector<T> Pull_data (  const std::vector<std::vector<T>> & data,
                            int row, int column_first, int column_last) {

  std::vector<T> output;
  output.resize(column_last - column_first + 1);
  for(int i = column_first; i <= column_last; ++i) {
    output[i-column_first] = data[row][i];
  }
  return output;
}

template <typename T>
std::vector<T> Sample_mean (  const std::vector<std::vector<T>> & data,
                              int column_first, int column_last) {

  std::vector<T> output;
  output.resize(column_last - column_first + 1);
  for(int i = 0; i < data.size(); ++i)
    for(int j = column_first; j <= column_last; ++j)
      output[j - column_first] += (T) data[i][j];
  for(int j = column_first; j <= column_last; ++j)
    output[j - column_first] /= data.size();
  return output;
}

template <typename T>
std::vector<T> Sample_sd  ( const std::vector<std::vector<T>> & data,
                            const std::vector<T> & mean,
                                  int column_first, int column_last) {

    std::vector<T> output;
    output.resize(column_last - column_first + 1);
    for(int i = 0; i < data.size(); ++i)
      for(int j = column_first; j <= column_last; ++j)
        output[j - column_first] +=
          (T) (data[i][j] - mean[j - column_first]) *
          (data[i][j] - mean[j - column_first]);
    for(int j = column_first; j <= column_last; ++j) {
      output[j - column_first] /= ( data.size() - 1);
      output[j - column_first] = sqrt(output[j - column_first]);
    }
    return output;
}
