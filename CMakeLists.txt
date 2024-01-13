cmake_minimum_required(VERSION 3.28)

project(EVENTLOOP)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/")

add_subdirectory(example)

add_library(EVENTLOOP Eventloop.cpp)