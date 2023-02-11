cmake_minimum_required(VERSION 3.24)
project(wordle)

set(CMAKE_CXX_STANDARD 20)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/wordle.js
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(wordle main.cpp token.cpp token.h search_word.cpp search_word.h filter.cpp filter.h js_parser.cpp js_parser.h)
