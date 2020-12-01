cmake_minimum_required(VERSION 3.17)
project(Solo)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
add_library(analysis SHARED
        src/proc_analysis.cpp
        inc/proc_analysis.h
        src/utils.cpp
        inc/utils.h
        inc/database_manipulation.h
        src/database_manipulation.cpp
        src/tests.cpp
        inc/tests.h inc/welcome_screen.h inc/info_screen.h inc/explore_screen.h)

add_executable(Solo src/main.cpp)
target_link_libraries(Solo analysis)

find_package (SQLite3)

include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (Solo ${SQLite3_LIBRARIES})

find_package (Threads)
target_link_libraries (Solo Threads::Threads)

find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
target_link_libraries(Solo Qt5::Widgets Qt5::DBus)