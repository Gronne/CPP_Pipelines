cmake_minimum_required(VERSION 3.12)
project(cpp_pipelines VERSION 0.0.1 DESCRIPTION "PLS Pipelines library")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Pipelines)
add_subdirectory(Example)
add_subdirectory(Test)