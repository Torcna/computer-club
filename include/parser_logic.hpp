#pragma once
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "default_data_structures.hpp"

class parser {
  std::ostream& os;
  bool is_valid_time(const std::string& time, int& hours, int& minutes);
  bool is_valid_username(const std::string& username);

 public:
  parser(std::ostream& os = std::cerr) : os(os){};
  bool validate_and_parse(std::istream& input, input_data& data);
  
};