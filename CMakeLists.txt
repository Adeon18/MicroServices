cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME MicroServices)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(task1 task1.cpp)
add_executable(task2_datarace task2_datarace.cpp)

find_package(hazelcast-cpp-client CONFIG REQUIRED)

target_link_libraries(task1 PRIVATE hazelcast-cpp-client::hazelcast-cpp-client)
target_link_libraries(task2_datarace PRIVATE hazelcast-cpp-client::hazelcast-cpp-client)
