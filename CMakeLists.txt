cmake_minimum_required(VERSION 3.10)
project(cli_timer LANGUAGES C)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

add_library(add_tm2nowtm_o OBJECT ./add_tm2nowtm.c)
set_property(TARGET add_tm2nowtm_o  PROPERTY C_STANDARD 99)

add_library(fill_in_tm_from_str_o OBJECT ./fill_in_tm_from_str.c)
set_property(TARGET fill_in_tm_from_str_o  PROPERTY C_STANDARD 99)

add_executable(cli_timer cli_timer.c)
set_property(TARGET cli_timer PROPERTY C_STANDARD 99)
target_compile_definitions(cli_timer PUBLIC  NDEBUG)
target_link_libraries(cli_timer PRIVATE $<TARGET_OBJECTS:add_tm2nowtm_o>)
target_link_libraries(cli_timer PRIVATE $<TARGET_OBJECTS:fill_in_tm_from_str_o>)

add_subdirectory(./tests)




