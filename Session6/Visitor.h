#ifndef CALCULATOR_VISITOR_H
#define CALCULATOR_VISITOR_H

#include "calculator.hpp"

namespace calculator {
    class Visitor {
        std::shared_ptr<state_t> state;
        
    public:
        explicit Visitor(state_t &state) 
            : state{std::make_shared<state_t>(state)} {}
        
        double visit(const term_t &t);
        
        double visit(const_t &c);

        double visit(var_t &v);

        double visit(const assign_t &a);

        double visit(const unary_t &u);

        double visit(const binary_t &b);
    };

} // calculator

#endif
