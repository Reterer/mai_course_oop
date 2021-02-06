cmake_minimum_required( VERSION 3.10 )

project( oop_exercise_02 LANGUAGES CXX )
# set( CMAKE_CXX_FLAGS "-Wall" )

set(TIME_POINT "src/time_point.cpp" "src/time_point.hpp")

add_executable( tests "src/tests.cpp" ${TIME_POINT} )

add_executable( ${CMAKE_PROJECT_NAME} "src/main.cpp" ${TIME_POINT} )