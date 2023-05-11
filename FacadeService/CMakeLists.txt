cmake_minimum_required(VERSION 3.23)
project(FacadeService)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog REQUIRED)
find_package(hazelcast-cpp-client CONFIG REQUIRED)
find_package(ppconsul)

add_executable(${PROJECT_NAME} main.cpp Service/FacadeService.hpp Service/FacadeService.cpp Controller/FacadeController.hpp Controller/FacadeController.cpp ../Model/MessageString.hpp)

# Taken from libhttp server github
include(cmake/FindLibHttpServer.cmake)
include(cmake/FindCpr.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE ../Model)

target_include_directories(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBCPR_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBCPR_LIBRARIES})

target_link_libraries(${PROJECT_NAME} hazelcast-cpp-client::hazelcast-cpp-client)

target_link_libraries(${PROJECT_NAME} ppconsul)

