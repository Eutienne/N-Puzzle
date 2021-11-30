cmake_minimum_required(VERSION 3.16.0)

# set the project name
project(N-puzzle_solver)

set(CMAKE_CXX_STANDARD 14)

# add the executable
add_executable(N-puzzle_solver 
    src/main.cpp
    src/nsolver.cpp
    src/npuzzle.cpp
    src/node.cpp)

add_executable(N-puzzle_Manuel 
    src/main_m.cpp
    src/display.cpp
    src/npuzzle.cpp
    src/node.cpp)

target_link_libraries(N-puzzle_Manuel PUBLIC
    -lncurses)

# # tell cmake that there is unittest
enable_testing()

set(Headers
    header/node.hpp
    header/npuzzle.hpp
    header/nsolver.hpp)

set(Sources
    src/main.cpp
    src/nsolver.cpp
    src/npuzzle.cpp
    src/node.cpp)

add_subdirectory(test)

add_subdirectory(ThirdParty/gtest)

add_library(N-puzzle_solver_lib STATIC ${Sources} ${Headers})

