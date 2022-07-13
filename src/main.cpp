#include<string>
#include<iostream>
#include"graph.h"

int main() {
    using namespace std;

    Graph graph;
    Element e_c = C;
    Element e_h = H;
    BondOrder bo_s = Single;

    graph.add_node(e_h);
    graph.add_node(e_c);
    graph.add_edge(0, 1, bo_s);
    graph.print_graph();
}
