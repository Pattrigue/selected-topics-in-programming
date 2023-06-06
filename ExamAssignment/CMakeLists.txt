cmake_minimum_required(VERSION 3.24)
project(StochSimLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

include(doctest.cmake)
include(benchmark.cmake)

enable_testing()
include_directories(src)

# Graphviz paths
set(GRAPHVIZ_INCLUDE_DIR "C:/Program Files/Graphviz/include")
set(GRAPHVIZ_LIBRARY_DIR "C:/Program Files/Graphviz/lib")

# Add Graphviz directories
include_directories(${GRAPHVIZ_INCLUDE_DIR})
link_directories(${GRAPHVIZ_LIBRARY_DIR})

# Add src subdirectory
add_subdirectory(src)

# Link StochSimLib to main executable
add_executable(StochSimLibMain main.cpp)

# Link Graphviz and StochSimLib and StochSimLibGraphing to main executable
target_link_libraries(StochSimLibMain PRIVATE StochSimLib StochSimLibGraphing cgraph gvc)

add_subdirectory(tests)
add_subdirectory(benchmark)
add_subdirectory(estimations)