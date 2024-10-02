cmake_minimum_required(VERSION 3.10)
project(custom_shell)

set(CMAKE_C_STANDARD 99)


include_directories(include)


add_executable(custom_shell src/main.c src/terminal.c)
