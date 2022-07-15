#include"NodeAttribute.h"

std::ostream& operator<<(std::ostream& os, const NodeContainer& c) {
    using namespace std;
    vector<string> ElementName({"H","C","N","O","Br"});
    os << "Element:" << ElementName[c.element_] << " | ";
    os << "Charge:" << c.charge_ << endl;
    return os;
}