cmake_minimum_required(VERSION 3.17)
project(Solo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(Qt5Charts REQUIRED)
find_package(Qt5 COMPONENTS Widgets DBus Charts REQUIRED)

include_directories(inc)

add_library(analysis SHARED
        src/proc_analysis.cpp
        inc/proc_analysis.h
        src/utils.cpp
        inc/utils.h
        inc/database_manipulation.h
        src/database_manipulation.cpp
        src/tests.cpp
        inc/tests.h inc/Screen.h inc/Screen_listeners.h inc/Screen_inits.h inc/Screen_preparations.h inc/Screen_manipulations.h inc/Screen_graphs_maker.h)

set(CMAKE_AUTOMOC ON)
QT5_WRAP_UI( UI_HDRS ${UI_FILES} )

add_executable(Solo src/main.cpp)
target_link_libraries(Solo analysis)

find_package (SQLite3)

include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (Solo ${SQLite3_LIBRARIES})

find_package (Threads)
target_link_libraries (Solo Threads::Threads)

target_link_libraries(Solo Qt5::Widgets Qt5::DBus Qt5::Charts)