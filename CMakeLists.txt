#Cmake do projektu todopro (tdp)
cmake_minimum_required(VERSION 2.8)
project(tdp)

add_definitions(-std=c++11)

set(BUILD_SHARED_LIBS true)

find_package(Boost COMPONENTS program_options)

include_directories(
    ${Boost_INCLUDE_DIRS}
)


#set(CMAKE_CXX_COMPILER clang++)

AUX_SOURCE_DIRECTORY(src SRC)
add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${Boost_LIBRARIES}
)

