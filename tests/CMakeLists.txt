cmake_minimum_required(VERSION 3.10)
project(TEST_2 LANGUAGES CXX C)
find_package(Catch2 3 REQUIRED)

# These tests can use the Catch2-provided main
add_executable(tests2 ./test_add_tm2nowtm.cpp ./test_fill_in_tm_from_str.cpp)
target_link_libraries(tests2 PRIVATE $<TARGET_OBJECTS:add_tm2nowtm_o>)
target_link_libraries(tests2 PRIVATE $<TARGET_OBJECTS:fill_in_tm_from_str_o>)
target_link_libraries(tests2 PRIVATE Catch2::Catch2WithMain)

