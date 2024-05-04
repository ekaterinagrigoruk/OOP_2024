cmake_minimum_required(VERSION 3.27)
project(SRT_subtitles)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(gtests)
include_directories(gtests/googletest/include)

add_executable(SRT_subtitles
        parser.cpp
        parser.h
        subtitle.h
        subtitles_player.cpp
        subtitles_player.h
        command.h
        subtitle_tests.cpp
        command_tests.cpp
        parser_tests.cpp
        sub_player_tests.cpp
        main.cpp)

target_link_libraries(SRT_subtitles gtest gtest_main)