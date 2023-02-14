cmake_minimum_required(VERSION 3.24)
project(NumberSeriesAssignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(NumberSeriesAssignment main.cpp NumberSeries.cpp NumberSeries.h
        Timer.cpp Timer.h)
