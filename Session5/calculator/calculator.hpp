#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace calculator {
    /** Type to capture the state of entire calculator (one number per variable): */
    using state_t = std::vector<double>;

    /** Forward declarations to get around circular dependencies: */
    class expr_t;

    enum class op_t {
        plus, minus, mul, div, assign
    };

    class term_t {
    public:
        term_t() = default;

        ~term_t() noexcept = default;

        // pure virtual double operator() (state_t &s) const:
        virtual double operator()(state_t &s) const = 0;
    };

    /** Class representing a constant */
    class const_t : public term_t {
        double m_value;

    public:
        explicit const_t(double value) : m_value{value} {}

        double operator()(state_t &s) const override {
            return m_value;
        }
    };

    /** Class representing a variable */
    class var_t : public term_t {
        size_t m_id;

        /** only friends are allowed to construct variable instances */
        explicit var_t(size_t id) : m_id{id} {}

    public:
        /** returns the value of the variable stored in a state */
        double operator()(state_t &s) const override {
            return s[m_id];
        }
        
        operator expr_t() const;
        
        [[nodiscard]] size_t id() const {
            return m_id;
        }

        /** evaluates an assignment to a given expression and returns the resulting value */
        double operator()(state_t&, const expr_t&) const;

        friend class symbol_table_t;
    };

    /** Class representing an assignment */
    class assign_t : public term_t {
        std::shared_ptr<var_t> var;
        std::shared_ptr<term_t> term;

        op_t op;
    public:
        assign_t(std::shared_ptr<var_t> var, std::shared_ptr<term_t> term, op_t op)
                : var{std::move(var)}, term{std::move(term)}, op{op} {}

        double operator()(state_t &s) const override {
            double value = (*term)(s);
            
            switch (op) {
                case op_t::assign:
                    s[var->id()] = value;
                    break;
                case op_t::plus:
                    s[var->id()] += value;
                    break;
                case op_t::minus:
                    s[var->id()] -= value;
                    break;
                case op_t::mul:
                    s[var->id()] *= value;
                    break;
                case op_t::div:
                    if (value == 0) {
                        throw std::logic_error{"division by zero"};
                    }

                    s[var->id()] /= value;
                    break;
                default:
                    throw std::logic_error{"invalid assignment operator"};
            }

            return value;
        }
    };

    /** Class representing a unary operator */
    class unary_t : public term_t {
        std::shared_ptr<term_t> term;
        op_t op;
    public:
        unary_t(std::shared_ptr<term_t> term, op_t op)
                : term{std::move(term)}, op{op} {}

        double operator()(state_t &s) const override {
            double value = (*term)(s);

            switch (op) {
                case op_t::plus:
                    return value;
                case op_t::minus:
                    return -value;
                default:
                    throw std::logic_error{"invalid unary operator"};
            }
        }
    };

    /** Class representing a binary operator */
    class binary_t : public term_t {
        std::shared_ptr<term_t> m_lhs;
        std::shared_ptr<term_t> m_rhs;
        op_t op;
    public:
        binary_t(std::shared_ptr<term_t> lhs, std::shared_ptr<term_t> rhs, op_t op)
                : m_lhs{std::move(lhs)}, m_rhs{std::move(rhs)}, op{op} {}

        double operator()(state_t &s) const override {
            double lhs = (*m_lhs)(s);
            double rhs = (*m_rhs)(s);

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
    };

    class symbol_table_t {
        std::vector<std::string> names;
        std::vector<double> initial;
    public:
        [[nodiscard]] var_t var(std::string name, double init = 0) {
            auto res = names.size();

            names.push_back(std::move(name));
            initial.push_back(init);

            return var_t{res};
        }

        [[nodiscard]] state_t state() const {
            return {initial};
        }
    };


    struct expr_t {
        std::shared_ptr<term_t> m_term;
        
        explicit expr_t(const var_t& v) {
            // implementation to create an expression tree from a single variable
            m_term = std::make_shared<var_t>(v);
        }
        
        // unary operator constructor
        expr_t(const expr_t& e, op_t op) {
            m_term = std::make_shared<unary_t>(e.m_term, op);
        }

        // binary operator constructor
        expr_t(const expr_t& e1, const expr_t& e2, op_t op) {
            m_term = std::make_shared<binary_t>(e1.m_term, e2.m_term, op);
        }
        
        // assignment constructor
        expr_t(const var_t& v, const expr_t& e) {
            m_term = std::make_shared<assign_t>(std::make_shared<var_t>(v), e.m_term, op_t::assign);
        }
        
        // call operator 
        double operator()(state_t &s) const {
            return (*m_term)(s);
        }
    };

    // conversion operator from var_t to expr_t
    var_t::operator expr_t() const {
        return expr_t(*this);
    }

    /** assignment operation */
    inline double var_t::operator()(state_t& s, const expr_t& e) const { return s[m_id] = e(s); }

    /** unary operators: */
    inline expr_t operator+(const expr_t& e) { return expr_t{e, op_t::plus}; }
    inline expr_t operator-(const expr_t& e) { return expr_t{e, op_t::minus}; }
    
    /** binary operators: */
    inline expr_t operator+(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, op_t::plus}; }
    inline expr_t operator-(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, op_t::minus}; }
    inline expr_t operator*(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, op_t::mul}; }
    inline expr_t operator/(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, op_t::div}; }
    inline expr_t operator<<=(const var_t& v, const expr_t& e) { return expr_t{v, e}; }
}

#endif // INCLUDE_ALGEBRA_HPP

