cmake_minimum_required(VERSION 3.28)

project(example)

include_directories("${CMAKE_SOURCE_DIR}/")

add_subdirectory(Timer)

add_executable(${PROJECT_NAME} example.cpp)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    EVENTLOOP
    TIMER
)