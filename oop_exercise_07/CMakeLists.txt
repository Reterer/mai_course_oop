cmake_minimum_required( VERSION 3.10 )

project( oop_exercise_07 LANGUAGES CXX )

add_executable( ${CMAKE_PROJECT_NAME} "src/main.cpp" "src/figure_factory.hpp" "src/figure.cpp"  "src/figure_factory.cpp" "src/figure.hpp" "src/point.cpp" "src/point.hpp")

set_target_properties(  ${CMAKE_PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
