#pragma once
#include<iostream>
#include"Node.h"

enum BondOrder {Single, Double, Aromatic, Triple};

class Edge {
    public:
        Node src_;
        Node dest_;
        size_t address_;
};

std::ostream& operator<<(std::ostream& os, const Edge& edge);
