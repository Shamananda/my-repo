cmake_minimum_required(VERSION 3.10)

project(Client CXX)

set(CMAKE_CXX_STANDARD 20)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

#set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
