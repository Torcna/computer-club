#include <gtest/gtest.h>

#include "header_club_manager.hpp"
#include "header_path_manager.hpp"
#include "parser_logic.hpp"

path_manager man;
#define VALIDATION_TESTS_PATH "wrong_input_format"
#define FUNC_TESTS_PATH "right_input_format"
TEST(test_validation, test1_wrong_data_extra_arg_id_3) {
  std::ifstream inputFile(man.get_test_path(VALIDATION_TESTS_PATH, "test1_wrong_data_extra_arg_id_3.txt"));
  input_data input_data_main;
  parser p;
  ASSERT_FALSE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();
}

TEST(test_validation, test2_wrong_data_hourly_rate_incorrect) {
  std::ifstream inputFile(man.get_test_path(VALIDATION_TESTS_PATH, "test2_wrong_data_hourly_rate_incorrect.txt"));
  input_data input_data_main;
  parser p;
  ASSERT_FALSE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();
}

TEST(test_validation, test3_wrong_data_extra_arg_id_2) {
  std::ifstream inputFile(man.get_test_path(VALIDATION_TESTS_PATH, "test3_wrong_data_extra_arg_id_2.txt"));
  input_data input_data_main;
  parser p;
  ASSERT_FALSE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();
}

TEST(test_validation, test4_wrong_data_desks_num_negative) {
  std::ifstream inputFile(man.get_test_path(VALIDATION_TESTS_PATH, "test4_wrong_data_desks_num_negative.txt"));
  input_data input_data_main;
  parser p;
  ASSERT_FALSE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();
}

TEST(test_validation, test5_wrong_data_missing_arg_id_4) {
  std::ifstream inputFile(man.get_test_path(VALIDATION_TESTS_PATH, "test5_wrong_data_missing_arg_id_4.txt"));
  input_data input_data_main;
  parser p;
  ASSERT_FALSE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();
}

TEST(test_validation, test6_wrong_data_unknown_id) {
  std::ifstream inputFile(man.get_test_path(VALIDATION_TESTS_PATH, "test6_wrong_data_unknown_id.txt"));
  input_data input_data_main;
  parser p;
  ASSERT_FALSE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();
}

TEST(test_validation, validation_pass_on_normal_data) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test1.txt"));
  input_data input_data_main;
  parser p;
  ASSERT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();
}

TEST(function_tests_correct_work, fuction_test_1) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test1.txt"));
  input_data input_data_main;
  parser p;
  EXPECT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  ASSERT_TRUE(manager.event_flow_handler());
}

TEST(function_tests_correct_work, fuction_test_2) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test2.txt"));
  input_data input_data_main;
  parser p;
  EXPECT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  ASSERT_TRUE(manager.event_flow_handler());
}
TEST(function_tests_correct_work, fuction_test_3) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test3.txt"));
  input_data input_data_main;
  parser p;
  EXPECT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  ASSERT_TRUE(manager.event_flow_handler());
}
TEST(function_tests_correct_work, fuction_test_4) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test4.txt"));
  input_data input_data_main;
  parser p;
  EXPECT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  ASSERT_TRUE(manager.event_flow_handler());
}

TEST(function_tests_correct_work, fuction_test_5) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test5.txt"));
  input_data input_data_main;
  parser p;
  EXPECT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  ASSERT_TRUE(manager.event_flow_handler());
}

TEST(function_tests_correct_work, fuction_test_6) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test6.txt"));
  input_data input_data_main;
  parser p;
  EXPECT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  ASSERT_TRUE(manager.event_flow_handler());
  manager.print_events();
}

TEST(function_tests_correct_work, fuction_test_7) {
  std::ifstream inputFile(man.get_test_path(FUNC_TESTS_PATH, "test7.txt"));
  input_data input_data_main;
  parser p;
  EXPECT_TRUE(p.validate_and_parse(inputFile, input_data_main));
  inputFile.close();

  club_work_manager manager(input_data_main, std::cout);

  ASSERT_TRUE(manager.event_flow_handler());
  manager.print_events();
}