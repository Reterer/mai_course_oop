cmake_minimum_required( VERSION 3.10 )

project( oop_exercise_03 LANGUAGES CXX )
# set( CMAKE_CXX_FLAGS "-Wall" )

set(FIGURE "src/figure.hpp" "src/figure.cpp" "src/point.hpp" "src/point.cpp")
add_executable( ${CMAKE_PROJECT_NAME} "src/main.cpp"  ${FIGURE})