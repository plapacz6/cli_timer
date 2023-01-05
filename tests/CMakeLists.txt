cmake_minimum_required(VERSION 3.10)
project(tests LANGUAGES CXX C)
find_package(Catch2 3 REQUIRED)

# These tests can use the Catch2-provided main
add_executable(tests test_add_tm2nowtm.cpp, test_fill_in_tm_from_str.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PUBLIC ..)


add_library(add_tm2nowtm add_tm2nowtm PROPERTY C_STANDARD 99)

add_executable(cli_timer cli_timer.c)
set_property(TARGET cli_timer PROPERTY C_STANDARD 99)
