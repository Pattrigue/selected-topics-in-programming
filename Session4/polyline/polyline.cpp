#include "polyline.h"

std::vector<point>::iterator polyline::begin() {
    return m_points.begin();
}

std::vector<point>::iterator polyline::end() {
    return m_points.end();
}

void polyline::clear() {
    m_points.clear();
}

void polyline::operator+=(const point &rhs) {
    m_points.push_back(rhs);
}

polyline::operator bool() const {
    return !m_points.empty();
}
