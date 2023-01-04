cmake_minimum_required(VERSION 3.10)
project(cli_timer LANGUAGES C)
add_executable(cli_timer cli_timer.c)
set_property(TARGET cli_timer PROPERTY C_STANDARD 99)




