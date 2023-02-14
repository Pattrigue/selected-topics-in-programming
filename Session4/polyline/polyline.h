#ifndef POLYLINE_POLYLINE_H
#define POLYLINE_POLYLINE_H


#include <vector>
#include <memory>
#include "point.h"

class polyline {
public:
    polyline () {
        std::cout << "Polyline default constructor." << std::endl;
    } 
    
    explicit polyline(const std::vector<point> &points) : m_points(std::make_shared<std::vector<point>>(points)) {
        std::cout << "Polyline custom constructor." << std::endl;
    }
    
    polyline (const polyline &other) : m_points(other.m_points) {
        std::cout << "Polyline copy constructor." << std::endl;
    } 
    
    [[nodiscard]] std::vector<point>::iterator begin() const; 
    [[nodiscard]] std::vector<point>::iterator end() const;
    
    void clear() const;
    [[nodiscard]] std::vector<point>* get() const;
    explicit operator bool () const;
    
    void operator+=(const point &rhs);
    polyline &operator=(const polyline &other);
private:
    std::shared_ptr<std::vector<point>> m_points = std::make_shared<std::vector<point>>();
};


#endif //POLYLINE_POLYLINE_H
