cmake_minimum_required(VERSION 3.17)
project(Solo)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
add_library(analysis SHARED src/proc_analysis.cpp inc/proc_analysis.h src/utils.cpp inc/utils.h)

add_executable(Solo src/main.cpp)
target_link_libraries(Solo analysis)