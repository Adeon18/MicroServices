cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME MicroServices)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(task1)
add_subdirectory(task2_datarace_test)
add_subdirectory(task3_bounded_queue)