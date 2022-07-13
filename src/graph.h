#include<string>
#include<vector>

class Node {
    int index;
    std::string element;
};

class Graph {
public:
    void print_size() const;
    std::vector<Node> nodes_;
};

