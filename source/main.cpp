#include "header_club_manager.hpp"
#include "header_path_manager.hpp"
#include "parser_logic.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "please specify file you want to open" << std::endl;
    return 1;
  }
  std::string filename = argv[1];
  std::string directory = "files_for_main_task";
  path_manager pm;
  input_data input_data_main;
  parser p;


  std::filesystem::path file_path = pm.get_main_task_data(directory, filename);
  std::ifstream inputFile(file_path);


  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file data.txt" << std::endl;
    return 1;
  }

  if (!p.validate_and_parse(inputFile, input_data_main)) {
    std::cerr << "Input validation failed." << std::endl;
    return -1;
  }
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  if (manager.event_flow_handler()) 
    {
    manager.print_events();
  }
  return 0;
}