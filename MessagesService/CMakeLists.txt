cmake_minimum_required(VERSION 3.23)
project(MessagesService)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog REQUIRED)
find_package(hazelcast-cpp-client CONFIG REQUIRED)

add_executable(MessagesService main.cpp Controller/MessageController.hpp ../Model/MessageUUID.hpp ../Model/MessageString.hpp Controller/MessageController.cpp Service/MessagesService.hpp Service/MessagesService.cpp Repository/MessageMemRepository.cpp Repository/MessageMemRepository.hpp)

# Taken from libhttp server github
include(cmake/FindLibHttpServer.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE ../Model)

target_include_directories(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})

target_link_libraries(${PROJECT_NAME} hazelcast-cpp-client::hazelcast-cpp-client)