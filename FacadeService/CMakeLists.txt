cmake_minimum_required(VERSION 3.23)
project(FacadeService)

set(CMAKE_CXX_STANDARD 20)

add_executable(FacadeService main.cpp)

# Taken from libhttp server github
include(cmake/FindLibHttpServer.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})