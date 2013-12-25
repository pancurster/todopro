#Cmake do projektu todopro (tdp)
cmake_minimum_required(VERSION 2.6)

project(todopro)
#add_definitions(-std=c++11)

#find_package(Boost COMPONENTS tuple)

set(CMAKE_CXX_COMPILER clang++)

AUX_SOURCE_DIRECTORY(../src SRC)
add_executable(todopro ${SRC})

