cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests.out Tests/tests.cpp)
target_link_libraries(runTests.out ${GTEST_LIBRARIES} pthread)