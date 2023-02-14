#include "point.h"


std::ostream &operator<<(std::ostream &os, const point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}
