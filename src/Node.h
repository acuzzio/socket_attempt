#pragma once
#include<iostream>
#include<vector>   
#include<string>

enum Element {H,C,N,O,Br};

class Node {
    public:
        size_t address_ {0};

    bool operator==(const Node& other) const {
        return (address_ == other.address_);
    }
};

std::ostream& operator<<(std::ostream& os, const Node& node);
