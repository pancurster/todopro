#Cmake do projektu todopro (tdp)
cmake_minimum_required(VERSION 2.8)
project(tdp)

add_definitions(-std=c++11 -Wall)

set(BUILD_SHARED_LIBS true)

find_package(Boost COMPONENTS program_options)

include_directories(
    ${Boost_INCLUDE_DIRS}
)

set(DEVEL 1 BOOL develop)
#option(DEVEL "on off devel compilation" OFF)

if (DEVEL EQUAL 1)
    message("-- DEV BUILD")

else (DEVEL)
    message("-- PRODUCTION BUILD")

    #Zapisywanie pliku w folderze roboczym lub w $HOME/
    #set_source_files_properties(todopro.cc
    #    PROPERTIES COMPILE_DEFINITIONS DB_FILE_HOME)
    add_definitions(-DDB_FILE_HOME)

endif(DEVEL EQUAL 1)


#set(CMAKE_CXX_COMPILER clang++)

AUX_SOURCE_DIRECTORY(src SRC)
add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${Boost_LIBRARIES}
)

