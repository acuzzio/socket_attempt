#include<string>
#include<vector>
#include<iostream>

enum BondOrder {Single, Double, Aromatic, Triple};

enum Element {H,C,N,O,Br};

class Edge {
    public:
        Edge(int src, int dest, BondOrder bo)
        : src_(src), dest_(dest), bo_(bo) {}
        int src_, dest_;
        BondOrder bo_;
};

class Node {
    public:
        Node(Element elem) 
        : element_(elem) {}
        Element element_;
        

};

std::ostream& operator<<(std::ostream& os, const Edge& edge);
std::ostream& operator<<(std::ostream& os, const Node& node);

class Graph {
public:
    std::vector<Node> nodes_;
    std::vector<Edge> edges_;

    void print_size() const;

    int size() const
    {
        return nodes_.size();
    }

    void add_node(Element elem)
    {
        Node node(elem);
        nodes_.emplace_back(node);
    }

    void add_edge(int src, int dest, BondOrder bo)
    {
        Edge edge(src, dest, bo);
        edges_.emplace_back(edge);
    }

    void print_graph() const
    {
        std::cout << "\nGraph size: " << nodes_.size() << std::endl;
        std::cout << "  Nodes:" << std::endl;
        for (const Node& node : nodes_) {
            std::cout << node << std::endl;
        }
        std::cout << "  Edges:" << std::endl;
        for (const Edge& edge : edges_) {
            std::cout << edge << std::endl;
        }
    }

};

