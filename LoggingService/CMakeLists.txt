cmake_minimum_required(VERSION 3.23)
project(LoggingService)

set(CMAKE_CXX_STANDARD 20)

add_executable(LoggingService main.cpp service/LoggingService.hpp service/LoggingService.cpp)

find_package(spdlog REQUIRED)

# Taken from libhttp server github
include(cmake/FindLibHttpServer.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})
