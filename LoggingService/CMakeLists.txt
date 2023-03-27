cmake_minimum_required(VERSION 3.23)
project(LoggingService)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(LoggingService main.cpp Controller/LoggingController.hpp Controller/LoggingController.cpp ../Model/Message.hpp Service/LoggingService.hpp Service/LoggingService.cpp Repository/MemoryRepository.hpp Repository/MemoryRepository.cpp Repository/HZRepository.hpp Repository/HZRepository.cpp)

find_package(spdlog REQUIRED)
find_package(hazelcast-cpp-client CONFIG REQUIRED)

# Taken from libhttp server github
include(cmake/FindLibHttpServer.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE ../Model)

target_include_directories(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})

target_link_libraries(${PROJECT_NAME} hazelcast-cpp-client::hazelcast-cpp-client)

