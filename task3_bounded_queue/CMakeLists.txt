cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME task3_bounded-queue)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(write_client write_client.cpp)

find_package(hazelcast-cpp-client CONFIG REQUIRED)

target_link_libraries(write_client PRIVATE hazelcast-cpp-client::hazelcast-cpp-client)

