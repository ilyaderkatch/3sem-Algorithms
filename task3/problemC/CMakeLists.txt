cmake_minimum_required(VERSION 3.15)
project(problemC)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -Wall -Wconversion -Wextra -Werror")

add_executable(problemC main.cpp)