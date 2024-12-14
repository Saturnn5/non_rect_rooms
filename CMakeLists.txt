cmake_minimum_required(VERSION 3.30)
project(non_rect_rooms)

set(CMAKE_CXX_STANDARD 20)

add_executable(non_rect_rooms main.cpp
        Generator.cpp
        Generator.h
        TwoDArray.h
        Utils.h)
