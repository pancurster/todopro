cmake_minimum_required (VERSION 2.8)
project (empty_project)


# General setup

add_definitions(-std=c++11)

set(BUILD_SHARED_LIBS true)

find_package(Boost COMPONENTS unit_test_framework thread program_options)

include_directories(
    ${Boost_INCLUDE_DIRS}
)

# production libs
AUX_SOURCE_DIRECTORY(../src SRC)

add_library(system_under_test 
    ${SRC}
    #../src/task.cc
    #../src/todopro.cc
    #../src/taskmanager.cc
    ############################
    # add production code here #
    ############################
)

                                        ###################################
set_target_properties(system_under_test # <- add implementation libs here # 
                                        ################################### 
    PROPERTIES COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
               LINK_FLAGS "-coverage"
)

add_executable(${CMAKE_PROJECT_NAME} main.cc)


target_link_libraries(${CMAKE_PROJECT_NAME} 
    ${Boost_LIBRARIES}
    system_under_test
    ############################
    # add production libs here #
    ############################
)


# helpers

add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME}
)

add_custom_target(coverage
    COMMAND find . -name *.gcda | xargs rm -vf
    COMMAND ${CMAKE_PROJECT_NAME}
    COMMAND lcov -c -d . -o coverage.info
    COMMAND lcov --remove coverage.info "*/usr/*" "*/opt/*" "*/boost/*" -o coverage.info
    COMMAND genhtml --legend coverage.info
)
