#ifndef POLYLINE_POLYLINE_H
#define POLYLINE_POLYLINE_H


#include <vector>
#include <memory>
#include "point.h"

class polyline {
public:
    polyline (const polyline &other) : m_points(other.m_points) { } // copy constructor
    
    std::vector<point>::iterator begin() const; 
    std::vector<point>::iterator end() const;
    
    void clear() const;
    explicit operator bool () const;
    
    void operator+=(const point &rhs);
    polyline &operator=(const polyline &other);
private:
    std::shared_ptr<std::vector<point>> m_points;
};


#endif //POLYLINE_POLYLINE_H
