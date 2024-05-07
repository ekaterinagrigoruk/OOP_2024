cmake_minimum_required(VERSION 3.27)
project(GPS_track)

add_subdirectory(gtests)
include_directories(gtests/googletest/include)

set(CMAKE_CXX_STANDARD 20)

add_library(pugixml
        puqixml/pugixml-master/src/pugixml.cpp
)

add_executable(GPS_track main.cpp
        geo_point.cpp
        geo_point.h
        histogram.cpp
        histogram.h
        gps_track.cpp
        gps_track.h
        parser.cpp
        parser.h
        geo_point_tests.cpp
        parser_tests.cpp
        histogram_tests.cpp
        gps_track_tests.cpp
)

target_include_directories(pugixml PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/src
)

target_link_libraries(GPS_track PRIVATE pugixml)
target_link_libraries(GPS_track PRIVATE gtest gtest_main)
