﻿#ifndef NUMBERSERIESASSIGNMENT_NUMBERSERIES_H
#define NUMBERSERIESASSIGNMENT_NUMBERSERIES_H

#include <vector>

class NumberSeries {
public:
    static NumberSeries make_random(size_t size);
    static NumberSeries make_random(size_t size, int min, int max);
    
    void add(int number);
    int min() const;
    int max() const;
    
    int operator+(const NumberSeries& rhs);
    NumberSeries& operator+=(const NumberSeries& rhs);
    bool operator<(const NumberSeries& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const NumberSeries& series);
private:
    std::vector<int> m_series;
    int m_min;
    int m_max;
};

#endif