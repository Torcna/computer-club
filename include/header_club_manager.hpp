#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "default_data_structures.hpp"

std::string format_time(size_t time);
class id_manager {
  size_t nextClientId;
  std::unordered_map<size_t, std::string> idToName;
  std::map<std::string, size_t> nameToId;

 public:
  static constexpr size_t INVALID_ID = 0;
  size_t register_name(const std::string& name);  // register clients as they arrive at club
  void remove_client(const std::string& name);    // remove client from club on id 4 and 11
  size_t get_id(const std::string& name) const;
  const std::string& get_name(size_t id) const { return idToName.at(id); }  // get name by id
  auto begin() { return nameToId.cbegin(); }  // return iterator for nameToId(used in send everyonehome)
  auto end() { return nameToId.cend(); }      // return iterator for nameToId(used in send everyonehome)
  void set_id_begin(size_t num) {
    nextClientId = num;
  }  // set nextClientId to prevent desks and clients id`s intersection
};
std::ostream& operator<<(std::ostream& os, const event& ev);
class club_work_manager {
  id_manager id_manager_inner;
  std::vector<computer_desk> desks;              // computers
  input_data& input_data_screen;                 // input data
  std::vector<event>& events;                    // all events during day
  std::set<size_t> clients_using_desks;          // set for quick checks
  std::queue<size_t> clients_waiting_for_desks;  // queue for waiting clients
  std::ostringstream os;                         // for collecting output
  std::ostream& ost;                             // type of output stream

  bool is_working_time(const event& ev);                                          // check if event is in working time
  size_t client_leaves_desk(size_t client_id, const event& ev, bool& desk_used);  // client leaving desk
  bool remove_client_from_queue(size_t client_id);                                // remove client from queue
  bool handle_event_id_1(const event& ev);
  bool handle_event_id_2(const event& ev);
  bool handle_event_id_3(const event& ev);
  bool handle_event_id_4(const event& ev);
  bool send_everyone_home();                     // send everyone home when its closing time
  void print_desk_statistics(std::ostream& os);  // desks statistics to os

 public:
  size_t gimme_desk1() { return desks[0].total_cash; }
  club_work_manager(input_data& data, std::ostream& ost);

  bool event_flow_handler();  // main function
  void print_events();        // use outstream to print events
};