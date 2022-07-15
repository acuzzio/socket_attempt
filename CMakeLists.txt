cmake_minimum_required(VERSION 3.14)

project(Graph VERSION 0.0)

add_executable(Graph
    src/main.cpp
    src/Graph.cpp
    src/Node.cpp
    src/Edge.cpp
    src/NodeAttribute.cpp
)

set_property(TARGET Graph PROPERTY CXX_STANDARD 14)
