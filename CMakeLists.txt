cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME MicroServices)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(LoggingService)
add_subdirectory(MessagesService)
add_subdirectory(FacadeService)
