#ifndef NUMBERSERIESASSIGNMENT_NUMBERSERIES_H
#define NUMBERSERIESASSIGNMENT_NUMBERSERIES_H

#include <vector>

class NumberSeries {
public:
    static void make_random(size_t size);
    int min() const;
    int max(); const;
    
    NumberSeries operator+(const NumberSeries& rhs);
    NumberSeries& operator+=(const NumberSeries& rhs);
    bool operator<(const NumberSeries& rhs);
private:
    std::vector<int> m_series;
    int m_min;
    int m_max;
};

#endif