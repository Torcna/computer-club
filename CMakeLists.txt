cmake_minimum_required(VERSION 3.14)
project(club)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(SOURCE_FILES
    source_realizations/club_manager_def.cpp
    source_realizations/parser_logic_def.cpp
    source_realizations/path_manager_def.cpp
)
set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(gtest)

add_executable(club
    source/main.cpp
    ${SOURCE_FILES}
)

include_directories(include)

add_executable(tests
    source_tests/tests_main.cpp
    source_tests/tests.cpp
    ${SOURCE_FILES}
)


target_compile_definitions(club PRIVATE PROJECT_ROOT="${PROJECT_ROOT}")
target_compile_definitions(tests PRIVATE PROJECT_ROOT="${PROJECT_ROOT}")



target_link_libraries(tests gtest)

