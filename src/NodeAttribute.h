#pragma once
#include"Graph.h"
#include<string>


class NodeContainer {
    public:
    Element element_{H};
    int charge_{0};
};

std::ostream& operator<<(std::ostream& os, const NodeContainer& c);

template <class Attribute>
class Attributes 
    : public std::vector<Attribute> {
    public:

    const Attribute& operator[](const Node& node) {
        return std::vector<Attribute>::operator[](node.address_);
    }

    const Attribute& operator[](const Edge& edge) {
        return std::vector<Attribute>::operator[](edge.address_);
    }
};
