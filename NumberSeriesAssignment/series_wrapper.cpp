#include "series_wrapper.h"

namespace series {
    NumberSeriesWrapper &NumberSeriesWrapper::operator=(const NumberSeriesWrapper &other) {
        if (this != &other) {
            m_series = std::make_unique<NumberSeries>(*other.m_series);
        }

        return *this;
    }

    NumberSeriesWrapper &NumberSeriesWrapper::operator=(NumberSeriesWrapper &&other) noexcept {
        if (this != &other) {
            m_series = std::move(other.m_series);
        }

        return *this;
    }
    
    NumberSeriesWrapper NumberSeriesWrapper::make_random(size_t size) {
        return make_random(size, INT_MIN, INT_MAX);
    }

    NumberSeriesWrapper NumberSeriesWrapper::make_random(size_t size, int min, int max) {
        NumberSeriesWrapper series_wrapper;
        series_wrapper.m_series->make_random(size, min, max);

        return series_wrapper;
    }

    void NumberSeriesWrapper::add(int number) {
        m_series->add(number);
    }

    int NumberSeriesWrapper::min() const {
        return m_series->min();
    }

    int NumberSeriesWrapper::max() const {
        return m_series->max();
    }

    int NumberSeriesWrapper::operator+(const NumberSeriesWrapper &rhs) {
        return *m_series + *rhs.m_series;
    }

    NumberSeriesWrapper &NumberSeriesWrapper::operator+=(const NumberSeriesWrapper &rhs) {
        *m_series += *rhs.m_series;
        return *this;
    }

    bool NumberSeriesWrapper::operator<(const NumberSeriesWrapper &rhs) const {
        return *m_series < *rhs.m_series;
    }

    std::ostream &operator<<(std::ostream &os, const NumberSeriesWrapper &series_wrapper) {
        os << *series_wrapper.m_series;
        return os;
    }
} 