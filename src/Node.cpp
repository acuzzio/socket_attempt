#include"Node.h"


std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << node.address_;
    return os;
}
