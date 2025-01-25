#include "parser_logic.hpp"


bool parser::is_valid_time(const std::string& time, size_t& hours, size_t& minutes) {
  if (time.size() != 5 || time[2] != ':') return false;

  try {
    hours = std::stoi(time.substr(0, 2));
    minutes = std::stoi(time.substr(3, 2));

  } catch (...) {
    return false;
  }

  return ((hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60));
}
bool parser::is_valid_username(const std::string& username) {
  if (username.empty()) {
    return false;
  }

  for (char ch : username) {
    if (!(std::isalnum(ch) || ch == '_' || ch == '-')) {
      return false;
    }
  }

  return true;
}



bool parser::validate_and_parse(std::istream& input, input_data& data) {
  std::string line;

  // table_count routine

  if (!std::getline(input, line)) {
    os << line << std::endl;
    return false;
  }
  try {
    data.table_count = std::stoi(line);
    if (data.table_count <= 0) {
      os << line << std::endl;
      return false;
    }
  } catch (...) {
    os << line << std::endl;
    return false;
  }

  // working time routine

  if (!std::getline(input, line)) {
    os << line << std::endl;
    return false;
  }
  std::istringstream lineStream(line);
  std::string temp;
  size_t hours, minutes;
  lineStream >> temp;
  if (!is_valid_time(temp, hours, minutes)) {
    os << line << std::endl;
    return false;
  }
  data.start_time = hours * 60 + minutes;
  temp.clear();
  lineStream >> temp;
  if (!is_valid_time(temp, hours, minutes)) {
    os << line << std::endl;
    return false;
  }
  data.end_time = hours * 60 + minutes;

  if (!(data.start_time <= data.end_time)) {
    os << line << std::endl;
    return false;
  }

  // hour_rate routine

  if (!std::getline(input, line)) {
    os << line << std::endl;
    return false;
  }
  auto is_positive_integer = [](const std::string& str) -> bool {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
  };
  if (!is_positive_integer(line)) {
    os << line << std::endl;
    return false;
  }

  data.hourly_rate = std::stoi(line);

  // event routine

  while (std::getline(input, line)) {
    std::istringstream lineStream(line);
    std::string time, body;
    int id;

    if (!(lineStream >> time >> id)) {
      os << line << std::endl;
      return false;
    }

    size_t hours_ev, minutes_ev;

    if (!is_valid_time(time, hours_ev, minutes_ev) || (id < 0 || id > 4)) {
      os << line << std::endl;
      return false;
    }

    std::getline(lineStream >> std::ws, body);

    std::istringstream body_stream(body);
    std::string username, second_word;
    if (!(body_stream >> username)) {
      os << line << std::endl;
      return false;
    }

    if (!is_valid_username(username)) {
      os << line << std::endl;
      return false;
    }

    if (body_stream >> second_word) {
      if (id == 2) {
        try {
          int second_number = std::stoi(second_word);
          if (second_number <= 0) {
            os << line << std::endl;
            return false;
          }
        } catch (...) {
          os << line << std::endl;
          return false;
        }
      } else {
        os << line << std::endl;
        return false;
      }

      if (body_stream >> second_word) {
        os << line << std::endl;
        return false;
      }
    }

    data.events.push_back({size_t(hours_ev * 60 + minutes_ev), id, body});
  }
  return true;
}
