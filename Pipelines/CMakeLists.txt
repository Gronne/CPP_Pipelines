cmake_minimum_required(VERSION 3.12)
project(PLS VERSION 0.0.1 DESCRIPTION "PLS Pipelines library")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(PLS SHARED
    source/PipeQueue.cpp
)