cmake_minimum_required(VERSION 3.27)
project(ImageSegmentation)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(gtests)
include_directories(gtests/googletest/include)

set(ENV{OPENCV_DIR} "C:\\tools\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

add_executable(ImageSegmentation main.cpp
        vertex.h
        edge.h
        graph.h
        creater_graph.cpp
        creater_graph.h
        kruskal_graph.cpp
        kruskal_graph.h
        segmenter_graph.cpp
        segmenter_graph.h
        mincut_graph.cpp
        mincut_graph.h
        vertex_tests.cpp
        edge_tests.cpp
        graph_tests.cpp
        creater_graph_tests.cpp
        kruskal_graph_tests.cpp
        mincut_graph_tests.cpp
)

target_link_libraries(ImageSegmentation PRIVATE gtest gtest_main ${OpenCV_LIBS})
