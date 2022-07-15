#pragma once
#include<string>
#include<vector>
#include<iostream>
#include"Node.h"
#include"Edge.h"

class Graph {
public:
    void push_back(const Node& node) { nodes_.push_back(node); }
    void push_back(const Edge& edge) { edges_.push_back(edge); }

/*    void setNodeAddress(size_t oldAddress, size_t newAddress) {
        nodes_[oldAddress].address_ = newAddress;
    }*/

    std::vector<Edge> adjacentEdges(const Node& node) {
        std::vector<Edge> neighbors;
        for (const Edge& edge : edges_) {
            if (edge.dest_ == node || edge.src_ == node) {
                neighbors.push_back(edge);
            }
        }
        return neighbors;
    }

    std::vector<Node> adjacentNodes(const Node& node) {
        std::vector<Node> neighbors;
        for (const Edge& edge : adjacentEdges(node)) {
            if (edge.dest_ == node) {
                neighbors.push_back(edge.src_);
            } else {
                neighbors.push_back(edge.dest_);
            }
        }
        return neighbors;
    }

    const std::vector<Node>& nodes() const { return nodes_; }
    const std::vector<Edge>& edges() const { return edges_; }
private:
    std::vector<Node> nodes_;
    std::vector<Edge> edges_;
};


std::ostream& operator<<(std::ostream& os, const Graph& graph);
