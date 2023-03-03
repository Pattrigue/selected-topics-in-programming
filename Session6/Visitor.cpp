#include "Visitor.h"

namespace calculator {
    double Visitor::visit(const_t &c) {
        return c.value();
    }

    double Visitor::visit(var_t &v) {
        return (*state)[v.id()];
    }

    double Visitor::visit(const assign_t &a) {
        op_t op = a.op();

        // the value we want to use in the assignment
        double value = (*a.term()).accept(*this);

        // get a reference to the variable in the state, so we can modify it
        double* var_value = &(*state)[a.acc()->id()];

        switch (op) {
            case op_t::assign:
                *var_value = value;
                break;
            case op_t::plus:
                *var_value += value;
                break;
            case op_t::minus:
                *var_value -= value;
                break;
            case op_t::mul:
                *var_value *= value;
                break;
            case op_t::div:
                if (value == 0) {
                    throw std::logic_error{"division by zero"};
                }

                *var_value /= value;
                break;
            default:
                throw std::logic_error{"invalid assignment operator"};
        }

        return *var_value;
    }

    double Visitor::visit(const unary_t &u) {
        double value = u.term().accept(*this);

        op_t op = u.op();

        switch (op) {
            case op_t::plus:
                return value;
            case op_t::minus:
                return -value;
            default:
                throw std::logic_error{"invalid unary operator"};
        }
    }

    double Visitor::visit(const binary_t &b) {
        double lhs = b.lhs().accept(*this);
        double rhs = b.rhs().accept(*this);

        op_t op = b.op();

        switch (op) {
            case op_t::plus:
                return lhs + rhs;
            case op_t::minus:
                return lhs - rhs;
            case op_t::mul:
                return lhs * rhs;
            case op_t::div:
                if (rhs == 0) {
                    throw std::logic_error{"division by zero"};
                }

                return lhs / rhs;
            default:
                throw std::logic_error{"invalid binary operator"};
        }
    }
} // calculator