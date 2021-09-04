cmake_minimum_required(VERSION 3.20)
project(2D_combat_simulator)

set(CMAKE_CXX_STANDARD 14)

file(COPY battlefield.txt DESTINATION ${CMAKE_BINARY_DIR})

add_executable(2D_combat_simulator main.cpp Simulator.cpp Simulator.h Soldier.cpp Soldier.h Level.cpp Level.h)
