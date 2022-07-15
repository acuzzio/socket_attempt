#include"Graph.h"
#include<string>
#include<iostream>


std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    os << "Nodes:\n";
    for (const Node& node : graph.nodes()) {
        os << node << std::endl; 
    }
    os << "Edge:\n";
    for (const Edge& edge : graph.edges()) {
        os << edge << std::endl;
    }
    return os;
}