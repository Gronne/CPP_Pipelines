cmake_minimum_required(VERSION 3.12)
project(PLS_Example VERSION 0.0.1 DESCRIPTION "PLS Pipelines example")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../Pipelines/include)
SET(SOURCE_FILES source/main.cpp)

add_executable(PLS_Example.out ${SOURCE_FILES})
link_directories(libPLS.so)