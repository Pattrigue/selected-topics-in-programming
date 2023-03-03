#include "Visitor.h"
namespace calculator {

    double term_t::accept(Visitor& v) const {
        return v.visit(*this);
    }
}