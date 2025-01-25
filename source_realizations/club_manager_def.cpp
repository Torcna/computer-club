#include "header_club_manager.hpp"

std::string format_time(size_t time) {
  size_t hours = time / 60;
  size_t minutes = time % 60;
  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
  return oss.str();
}

std::ostream& operator<<(std::ostream& os, const event& ev) {
  os << format_time(ev.time) << " " << ev.id << " " << ev.body << "\n";
  return os;
}

size_t id_manager::register_name(const std::string& name) {
  if (nameToId.count(name) > 0) {
    return INVALID_ID;
  }
  size_t newId = nextClientId++;
  nameToId[name] = newId;
  idToName[newId] = name;
  return newId;
}

void id_manager::remove_client(const std::string& name) {
  size_t clientId = get_id(name);
  if (clientId != INVALID_ID) {
    nameToId.erase(name);
    idToName.erase(clientId);
  }
}

size_t id_manager::get_id(const std::string& name) const {
  if (nameToId.count(name) > 0) {
    return nameToId.at(name);
  }
  return INVALID_ID;
}

bool club_work_manager::is_working_time(const event& ev) {
  if (ev.time <= input_data_screen.end_time && ev.time >= input_data_screen.start_time) {
    return true;
  }
  return false;
}

size_t club_work_manager::client_leaves_desk(size_t client_id, const event& ev, bool& desk_used) {
  for (size_t i = 0, end = desks.size(); i != end; ++i) {
    if (desks[i].client_id == client_id) {
      size_t minutes_elapsed = ev.time - desks[i].time;
      size_t hours_elapsed = minutes_elapsed / 60;
      // earn some money
      desks[i].total_cash += (hours_elapsed + ((minutes_elapsed % 60 > 0) ? 1 : 0)) * input_data_screen.hourly_rate;
      // collect statistics
      desks[i].time_spent_total += minutes_elapsed;
      desks[i].is_busy_rn = false;
      clients_using_desks.erase(client_id);
      desk_used = true;
      return i;
    }
  }
  return 0;
}

bool club_work_manager::remove_client_from_queue(size_t client_id) {
  bool flag = false;
  std::queue<size_t> temp_q;
  size_t sz = clients_waiting_for_desks.size();
  for (int i = 0; i != sz; ++i) {
    auto temp_el = clients_waiting_for_desks.front();
    if (temp_el != client_id) {
      temp_q.push(temp_el);
    } else {
      flag = true;
    }
    clients_waiting_for_desks.pop();
  }
  clients_waiting_for_desks = temp_q;
  return flag;
}

bool club_work_manager::handle_event_id_1(const event& ev) {
  const std::string& clientName = ev.body;

  size_t clientId = id_manager_inner.get_id(clientName);

  if (clientId != id_manager_inner.INVALID_ID) {
    event event_to_print = {ev.time, 13, "YouShallNotPass"};
    os << event_to_print;
    return false;
  }

  if (!is_working_time(ev)) {
    event event_to_print = {ev.time, 13, "NotOpenYet"};
    os << event_to_print;
    return false;
  }

  clientId = id_manager_inner.register_name(clientName);
  if (clientId == id_manager_inner.INVALID_ID) {
    os << "Error: Failed to register client";
    return false;
  }
  return true;
}

bool club_work_manager::handle_event_id_2(const event& ev) {
  std::istringstream iss(ev.body);
  std::string username;
  int table_number;
  iss >> username >> table_number;
  table_number--;

  // registered?
  size_t client_id = id_manager_inner.get_id(username);
  if (client_id == id_manager_inner.INVALID_ID) {
    event error_event = {ev.time, 13, "ClientUnknown"};
    os << error_event;
    return false;
  }
  // take a new desk?

  if (desks[table_number].is_busy_rn) {
    event error_event = {ev.time, 13, "PlaceIsBusy"};
    os << error_event;
    return false;
  }

  // free mine
  bool desk_used = false;
  client_leaves_desk(client_id, ev, desk_used);

  desks[table_number].is_busy_rn = true;
  desks[table_number].client_id = client_id;
  desks[table_number].time = ev.time;
  clients_using_desks.insert(client_id);
  return true;
}

bool club_work_manager::handle_event_id_3(const event& ev) {
  std::string username = ev.body;

  // is registered?
  size_t client_id = id_manager_inner.get_id(username);
  if (client_id == id_manager_inner.INVALID_ID) {
    event error_event = {ev.time, 13, "ClientUnknown"};
    os << error_event;
    return false;
  }
  // waiting over nothing?
  bool all_desks_busy = true;

  for (auto& t : desks) {
    if (!t.is_busy_rn) {
      all_desks_busy = false;
      break;
    }
  }

  if (!all_desks_busy) {
    event err_event = {ev.time, 13, "ICanWaitNoLonger!"};
    os << err_event;
    return false;
  }

  // queue is overloaded?
  if (clients_waiting_for_desks.size() > input_data_screen.table_count) {
    id_manager_inner.remove_client(username);  // check if removes properly
    event err_event = {ev.time, 11, username};
    os << err_event;
    return false;
  }

  clients_waiting_for_desks.push(client_id);
  return true;
}

bool club_work_manager::handle_event_id_4(const event& ev) {
  std::string username = ev.body;
  size_t client_id = id_manager_inner.get_id(username);
  if (client_id == id_manager_inner.INVALID_ID) {
    event error_event = {ev.time, 13, "ClientUnknown"};
    os << error_event;
    return false;
  }

  // leave desk && if wasn`t using a desk remove from queue and registered
  bool client_was_using_a_desk = false;
  auto desk_id = client_leaves_desk(client_id, ev, client_was_using_a_desk);
  if (!client_was_using_a_desk) {
    remove_client_from_queue(client_id);
  }
  id_manager_inner.remove_client(username);
  if (!clients_waiting_for_desks.empty() && client_was_using_a_desk) {
    auto& desk = desks[desk_id];
    size_t client_id = clients_waiting_for_desks.front();
    clients_waiting_for_desks.pop();
    desk.client_id = client_id;
    desk.time = ev.time;
    desk.is_busy_rn = true;
    clients_using_desks.insert(client_id);
    event event_to_print = {ev.time, 12, id_manager_inner.get_name(client_id) + " " + std::to_string(desk_id + 1)};
    os << event_to_print;
  }
  return true;
}

bool club_work_manager::send_everyone_home() {
  for (auto it = id_manager_inner.begin(), end = id_manager_inner.end(); it != end; ++it) {
    size_t client_id = it->second;
    bool desk_used = false;
    if (clients_using_desks.count(client_id) > 0) {
      size_t desk_id = client_leaves_desk(client_id, {input_data_screen.end_time, 0, ""}, desk_used);
    }
    event event_to_print = {input_data_screen.end_time, 11, it->first};
    os << event_to_print;
  }
  return true;
}

void club_work_manager::print_desk_statistics(std::ostream& os) {
  int i = 1;
  for (const auto& desk : desks) {
    os << i << " " << desk.total_cash << " " << format_time(desk.time_spent_total) << std::endl;
    ++i;
  }
}

club_work_manager::club_work_manager(input_data& data, std::ostream& ost = std::cout)
    : input_data_screen(data), events(data.events), ost(ost) {
  desks.reserve(data.table_count);
  for (size_t i = 0; i < data.table_count; ++i) {
    desks.emplace_back(false, 0, 0, 0, 0);
  }
  id_manager_inner.set_id_begin(data.table_count + 1);
}

bool club_work_manager::event_flow_handler() {
  os << format_time(input_data_screen.start_time) << std::endl;
  for (const auto& ev : events) {
    os << ev;
    if (ev.id == 1) {
      handle_event_id_1(ev);
    } else if (ev.id == 2) {
      handle_event_id_2(ev);
    } else if (ev.id == 3) {
      handle_event_id_3(ev);
    } else if (ev.id == 4) {
      handle_event_id_4(ev);
    }
  }
  if (!send_everyone_home()) {
    return false;
  }
  os << format_time(input_data_screen.end_time) << std::endl;
  print_desk_statistics(os);
  return true;
}
void club_work_manager::print_events() { ost << os.str(); }