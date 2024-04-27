cmake_minimum_required(VERSION 3.27)
project(OOP2024)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(gtests)
include_directories(gtests/googletest/include)

add_executable(OOP2024
        circularbuffer.cpp
        circularbuffer.h
        test.cpp)

target_link_libraries(OOP2024 gtest gtest_main)
