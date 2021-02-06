cmake_minimum_required( VERSION 3.0 )

project( oop_exercise_01 LANGUAGES CXX )
set( CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++14 -Isrc" )

include_directories(src)
file(GLOB_RECURSE SOURCE src/*.cpp)

add_executable( ${CMAKE_PROJECT_NAME} ${SOURCE} )