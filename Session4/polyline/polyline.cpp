#include "polyline.h"

std::vector<point>::iterator polyline::begin() const {
    return m_points->begin();
}

std::vector<point>::iterator polyline::end() const {
    return m_points->end();
}

void polyline::clear() const {
    m_points->clear();
}

polyline::operator bool() const {
    return !m_points->empty();
}

void polyline::operator+=(const point &rhs) {
    // Check if the reference count of m_points is greater than 1. 
    if (m_points.use_count() > 1) 
    {
        // If so, create a new instance of std::vector<point> and copy the content of m_points into it. 
        // Then, reset m_points to the new instance.
        m_points = std::make_shared<std::vector<point>>(*m_points);
    }
    
    m_points->push_back(rhs);
}

polyline &polyline::operator=(const polyline &other) {
    m_points = other.m_points;
    return *this;
}
