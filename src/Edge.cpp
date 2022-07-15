#include"Edge.h"


std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << "    " << edge.src_ << " -> " << edge.dest_;
    return os;
}
