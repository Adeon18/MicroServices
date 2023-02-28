cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME task3_bounded-queue)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(task3_queue task3_queue.cpp)

find_package(hazelcast-cpp-client CONFIG REQUIRED)

target_link_libraries(task3_queue PRIVATE hazelcast-cpp-client::hazelcast-cpp-client)

