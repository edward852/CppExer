cmake_minimum_required(VERSION 3.8)
project(Inheritance)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -fdump-class-hierarchy")
add_executable(Inheritance ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(Inheritance libdl.so)