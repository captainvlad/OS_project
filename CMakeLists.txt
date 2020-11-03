cmake_minimum_required(VERSION 3.17)
project(Solo)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
add_library(analysis SHARED src/proc_analysis.cpp inc/proc_analysis.h src/utils.cpp inc/utils.h inc/database_manipulation.h src/database_manipulation.cpp)

add_executable(Solo src/main.cpp)
target_link_libraries(Solo analysis)

find_package (SQLite3)

include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (Solo ${SQLite3_LIBRARIES})