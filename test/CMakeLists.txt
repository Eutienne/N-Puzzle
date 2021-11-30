cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_CXX_STANDARD 14)

# set the project name
project(N-puzzle_test)


set(Sources
    test.cpp
    valid.cpp
    invalid.cpp
    unsolvable.cpp)

# add the executable
add_executable(N-puzzle_test ${Sources})



add_test(
    NAME N-puzzle_test
    COMMAND N-puzzle_test
)
target_link_libraries(N-puzzle_test PUBLIC 
    N-puzzle_solver_lib gtest
)