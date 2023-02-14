#ifndef NUMBERSERIESASSIGNMENT_SERIES_WRAPPER_H
#define NUMBERSERIESASSIGNMENT_SERIES_WRAPPER_H

#include <memory>
#include "number_series.h"

namespace series {
    class NumberSeriesWrapper {
    public:
        // ...
    private:
        std::unique_ptr<NumberSeries> m_series;
    };
}

#endif
