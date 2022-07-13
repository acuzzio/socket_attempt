#include"graph.h"
#include<string>
#include<iostream>

void Graph::print_size() const {
	std::cout << "number of Nodes: " << nodes_.size() << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "    " << node.element_;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << "    Source: " << edge.src_ << " | Destination: " << edge.dest_ << " | Bond Order: " << edge.bo_;
    return os;
}