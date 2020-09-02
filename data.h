#ifndef DATA_H
#define DATA_H

#include <string>
#include <fstream>

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
  for(int i = 0; i < rows; ++i) data[i].resize(columns);

  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < columns; ++j) {
      file_stream >> data[i][j];
      if(j < columns - 1 ) file_stream >> temp;
    }
  }
}

template <typename T>
void CSV_random_partition ( const std::vector<std::vector<T>> data,
                            const std::vector<float> partition,
                                  std::vector<std::vector<std::vector<T>>> & p_data) {

  std::cout<<"hello";

  
}

#endif
