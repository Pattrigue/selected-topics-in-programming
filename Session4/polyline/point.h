#ifndef POLYLINE_POINT_H
#define POLYLINE_POINT_H

#include <iostream>


class point {
public:
    double x;
    double y;
    
    friend std::ostream &operator<<(std::ostream &os, const point &point);
};


#endif 
