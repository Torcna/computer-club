#include "header_path_manager.hpp"

std::filesystem::path path_manager::get_main_task_data(const std::string& directory, const std::string& filename) {
  std::filesystem::path project_root = PROJECT_ROOT;
  return project_root / directory / filename;
}

std::filesystem::path path_manager::get_test_path(const std::string& directory, const std::string& filename) {
  std::filesystem::path tests_path = PROJECT_ROOT;
  tests_path = tests_path / "files_for_tests" / directory / filename;
  return tests_path;
}