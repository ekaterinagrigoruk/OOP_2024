cmake_minimum_required(VERSION 3.27)
project(GraphTraversal)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(gtests)
include_directories(gtests/googletest/include)

add_executable(GraphTraversal main.cpp
        graph.cpp
        graph.h
        vertex.h
        edge.h
        parser.cpp
        parser.h
        Traversal.cpp
        Traversal.h
        edge_tests.cpp
        vertex_tests.cpp
        graph_tests.cpp
        parser_tests.cpp
        traversal_tests.cpp
)

target_link_libraries(GraphTraversal gtest gtest_main)