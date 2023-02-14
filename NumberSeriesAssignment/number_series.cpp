#include <random>
#include <iostream>
#include "number_series.h"

namespace series {
    NumberSeries NumberSeries::make_random(size_t size, int min, int max) {
        NumberSeries series;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);

        for (size_t i = 0; i < size; i++) {
            series.add(dis(gen));
        }

        return series;
    }

    NumberSeries NumberSeries::make_random(size_t size) {
        return make_random(size, INT_MIN, INT_MAX);
    }

    void NumberSeries::add(int number) {
        m_series.push_back(number);
        if (m_series.size() == 1) {
            m_min = number;
            m_max = number;
        } else {
            if (number < m_min) {
                m_min = number;
            }
            if (number > m_max) {
                m_max = number;
            }
        }
    }

    int NumberSeries::min() const {
        return m_min;
    }

    int NumberSeries::max() const {
        return m_max;
    }

    int NumberSeries::operator+(const NumberSeries &rhs) {
        size_t size = m_series.size() > rhs.m_series.size() ? m_series.size() : rhs.m_series.size();
        int sum = 0;

        for (std::size_t i = 0; i < size; i++) {
            if (i < m_series.size() && i < rhs.m_series.size()) {
                sum += m_series[i] + rhs.m_series[i];
            } else if (i < m_series.size()) {
                sum += m_series[i];
            } else if (i < rhs.m_series.size()) {
                sum += rhs.m_series[i];
            }
        }

        return sum;
    }

    NumberSeries &NumberSeries::operator+=(const NumberSeries &rhs) {
        size_t size = m_series.size() > rhs.m_series.size() ? m_series.size() : rhs.m_series.size();

        for (std::size_t i = 0; i < size; i++) {
            if (i < m_series.size() && i < rhs.m_series.size()) {
                m_series[i] += rhs.m_series[i];
            } else if (i < m_series.size()) {
                m_series[i] += 0;
            } else if (i < rhs.m_series.size()) {
                m_series.push_back(rhs.m_series[i]);
            }
        }
        
        return *this;
    }

    bool NumberSeries::operator<(const NumberSeries &rhs) const {
        int amplitude = m_max - m_min;
        int amplitude_rhs = rhs.m_max - rhs.m_min;

        return amplitude < amplitude_rhs;
    }

    std::ostream &operator<<(std::ostream &os, const NumberSeries &series) {
        os << "{";

        for (std::size_t i = 0; i < series.m_series.size(); i++) {
            os << series.m_series[i];

            if (i < series.m_series.size() - 1) {
                os << ", ";
            }
        }

        os << "}";

        return os;
    }
}
