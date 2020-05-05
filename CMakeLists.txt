cmake_minimum_required(VERSION 3.15)
project(MazeRouting)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(output "output.txt")

foreach (file IN LISTS output)
    configure_file(${file} ${file} COPYONLY)
endforeach ()

add_executable(MazeRouting main.cpp mainDriver.cpp mainDriver.h LeeAlgorithm.cpp LeeAlgorithm.h Vertex.h RecursiveBacktracking.cpp RecursiveBacktracking.h userInterface.cpp userInterface.h)