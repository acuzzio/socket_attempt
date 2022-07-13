#include<string>
#include<iostream>
#include"graph.h"

int main() {
    using namespace std;
    string hello("Hello World!");
    cout << hello << endl;
    Graph graph;
    Node node;
    graph.print_size();
    graph.nodes_.emplace_back(node);
    graph.print_size();
}
