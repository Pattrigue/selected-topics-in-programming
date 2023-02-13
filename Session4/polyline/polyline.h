#ifndef POLYLINE_POLYLINE_H
#define POLYLINE_POLYLINE_H


#include <vector>
#include "point.h"

class polyline {
public:
    std::vector<point>::iterator begin();    
    std::vector<point>::iterator end(); 
    
    void operator+=(const point &rhs);
private:
    std::vector<point> m_points;
};


#endif //POLYLINE_POLYLINE_H
