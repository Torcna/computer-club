#pragma once
struct event {
  size_t time;
  int id;
  std::string body;
};
struct input_data {
  size_t table_count{};
  size_t start_time{};
  size_t end_time{};

  size_t hourly_rate{};

  std::vector<event> events;
};
struct computer_desk {
  bool is_busy_rn = false;
  size_t client_id;
  size_t time;
  size_t time_spent_total;
  size_t total_cash;
};