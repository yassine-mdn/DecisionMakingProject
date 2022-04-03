cmake_minimum_required(VERSION 3.21)
project(DecisionMakingProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(DMP main.cpp Matrice.cpp Matrice.h Output.cpp Output.h Resolution.cpp Resolution.h)
