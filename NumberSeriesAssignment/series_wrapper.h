#ifndef NUMBERSERIESASSIGNMENT_SERIES_WRAPPER_H
#define NUMBERSERIESASSIGNMENT_SERIES_WRAPPER_H

#include <memory>
#include "number_series.h"

namespace series {
    class NumberSeriesWrapper {
    public:
        NumberSeriesWrapper()
                : m_series(std::make_unique<NumberSeries>()) {} // default constructor

        NumberSeriesWrapper(const NumberSeriesWrapper &other)
                : m_series(std::make_unique<NumberSeries>(*other.m_series)) {} // copy constructor

        NumberSeriesWrapper(NumberSeriesWrapper &&other) noexcept
                : m_series(std::move(other.m_series)) {} // move constructor
        
        NumberSeriesWrapper &operator=(const NumberSeriesWrapper &other); // copy assignment operator
        
        NumberSeriesWrapper &operator=(NumberSeriesWrapper &&other) noexcept; // move assignment operator

        static NumberSeriesWrapper make_random(size_t size);

        static NumberSeriesWrapper make_random(size_t size, int min, int max);

        void add(int number);

        int min() const;

        int max() const;

        int operator+(const NumberSeriesWrapper &rhs);

        NumberSeriesWrapper &operator+=(const NumberSeriesWrapper &rhs);

        bool operator<(const NumberSeriesWrapper &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const NumberSeriesWrapper &series);

    private:
        std::unique_ptr<NumberSeries> m_series;
    };
}

#endif
