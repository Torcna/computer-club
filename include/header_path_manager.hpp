#pragma once
#include <filesystem>
#include <string>

struct path_manager {
  std::filesystem::path get_main_task_data(const std::string& directory,
                                           const std::string& filename);  // returns right path to main task (not tests)
  std::filesystem::path get_test_path(const std::string& directory,
                                      const std::string& filename);  // returns right path to tests folder
};