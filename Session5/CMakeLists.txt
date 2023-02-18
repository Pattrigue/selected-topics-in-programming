cmake_minimum_required(VERSION 3.24)
project (Session5)

set(CMAKE_CXX_STANDARD 20)

add_executable(Session5 main.cpp Base.cpp Base.h Derived.cpp Derived.h Timer.h Timer.cpp)
