cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME task1)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} task1.cpp)


find_package(hazelcast-cpp-client CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE hazelcast-cpp-client::hazelcast-cpp-client)

