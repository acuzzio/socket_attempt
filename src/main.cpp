#include<string>
#include<iostream>
#include"Graph.h"
#include"NodeAttribute.h"

int main() {
    using namespace std;

    Graph graph;
    graph.push_back(Node{0});
    graph.push_back(Node{1});
    graph.push_back(Node{2});
    graph.push_back(Node{3});

    graph.push_back(Edge{0,1,0});
    graph.push_back(Edge{1,2,1});
    graph.push_back(Edge{2,3,2});
    graph.push_back(Edge{3,0,3});

    cout << graph << endl;

    Attributes<NodeContainer> nodeInfo;
    nodeInfo.push_back({H, 0});
    nodeInfo.push_back({C, -1});

    for (const NodeContainer& c : nodeInfo) {
        cout << c << endl;
    }

    cout << "Neighbor edges of 2:\n";
    vector<Edge> neighbors = graph.adjacentEdges({2});
    for (const Edge& edge : neighbors) {
        cout << edge << endl;
    }

    cout << "Neighbor of 2:\n";
    vector<Node> neighbors_2 = graph.adjacentNodes({2});
    for (const Node& node : neighbors_2) {
        cout << node << endl;
    }

}
