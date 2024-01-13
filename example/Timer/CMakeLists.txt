cmake_minimum_required(VERSION 3.28)

include_directories("${CMAKE_SOURCE_DIR}/")

add_library(TIMER STATIC Timer.cpp)