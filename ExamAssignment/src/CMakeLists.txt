cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

# source files without the 'src/' prefix
set(SOURCE_FILES
        Simulation.cpp
        Species.cpp
        Reaction.cpp
        ReactionCompounds.cpp
        ParallelSimulationRunner.cpp
        SimulationFileWriter.cpp
        ThreadPool.hpp)

add_library(StochSimLib ${SOURCE_FILES})

add_subdirectory(networks)
add_subdirectory(graphs)
