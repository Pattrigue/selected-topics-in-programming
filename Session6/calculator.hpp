#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Visitor.h"


namespace calculator {
    /** Type to capture the state of entire calculator (one number per variable): */
    using state_t = std::vector<double>;

    /** Forward declarations to get around circular dependencies: */
    class expr_t;
    
    enum class op_t {
        plus, minus, mul, div, assign
    };

    class Visitor;

    /** Abstract class representing a m_term in an expression */
    class term_t {
    public:
        term_t() = default;

        virtual ~term_t() noexcept = default;

        double accept(Visitor& v) const; 
    };


    /** Class representing a constant */
    class const_t : public term_t {
        double m_value;

    public:
        explicit const_t(double value) : m_value{value} {}

        double value() { return m_value; }
    };


    /** Class representing a variable */
    class var_t : public term_t {
        size_t m_id;

        /** only friends are allowed to construct variable instances */
        explicit var_t(size_t id) : m_id{id} {}

    public:
        operator expr_t() const;

        [[nodiscard]] size_t id() const {
            return m_id;
        }

        /** evaluates an assignment to a given expression and returns the resulting value */
        double operator()(state_t &, const expr_t &) const;

        friend class symbol_table_t;

        var_t(expr_t expr);
    };


    /** Class representing an assignment */
    class assign_t : public term_t {
        std::shared_ptr<var_t> m_acc;
        std::shared_ptr<term_t> m_term;

        op_t m_op;
    public:
        assign_t(std::shared_ptr<var_t> var, std::shared_ptr<term_t> term, op_t op)
                : m_acc{std::move(var)}, m_term{std::move(term)}, m_op{op} {}
        
        const std::shared_ptr<var_t> acc() const { return m_acc; }
        
        const std::shared_ptr<term_t> term() const { return m_term; }
        
        const op_t op() const { return m_op; }
    };


    /** Class representing a unary operator */
    class unary_t : public term_t {
        std::shared_ptr<term_t> m_term;
        op_t m_op;
    public:
        unary_t(std::shared_ptr<term_t> term, op_t op)
                : m_term{std::move(term)}, m_op{op} {}
        
        op_t op() const { return m_op; }
        
        term_t &term() const { return *m_term; }
    };


    /** Class representing a binary operator */
    class binary_t : public term_t {
        std::shared_ptr<term_t> m_lhs;
        std::shared_ptr<term_t> m_rhs;
        op_t m_op;
    public:
        binary_t(std::shared_ptr<term_t> lhs, std::shared_ptr<term_t> rhs, op_t op)
                : m_lhs{std::move(lhs)}, m_rhs{std::move(rhs)}, m_op{op} {}
                
        term_t &lhs() const { return *m_lhs; }
        
        term_t &rhs() const { return *m_rhs; }
        
        op_t op() const { return m_op; }
    };
    
    
    /** Class representing a symbol table */
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
        
        // implementation to create an expression tree from a single variable
        explicit expr_t(const var_t &v) {
            m_term = std::make_shared<var_t>(v);
        }

        // unary operator constructor
        expr_t(const expr_t &e, op_t op) {
            m_term = std::make_shared<unary_t>(e.m_term, op);
        }

        // binary operator constructor
        expr_t(const expr_t &e1, const expr_t &e2, op_t op) {
            m_term = std::make_shared<binary_t>(e1.m_term, e2.m_term, op);
        }

        // assignment constructor
        expr_t(const var_t &v, const expr_t &e, op_t op) {
            m_term = std::make_shared<assign_t>(std::make_shared<var_t>(v), e.m_term, op);
        }

        // const constructor
        expr_t(double i) {
            m_term = std::make_shared<const_t>(i);
        }
    };


    // conversion operator from var_t to expr_t
    var_t::operator expr_t() const { return expr_t(*this); }

    var_t::var_t(expr_t expr) {
        throw std::logic_error("assignment destination must be a variable expression");
    }

    /** unary operators: */
    inline expr_t operator+(const expr_t &e) { return expr_t{e, op_t::plus}; }

    inline expr_t operator-(const expr_t &e) { return expr_t{e, op_t::minus}; }

    /** binary operators: */
    inline expr_t operator+(const expr_t &e1, const expr_t &e2) { return expr_t{e1, e2, op_t::plus}; }

    inline expr_t operator-(const expr_t &e1, const expr_t &e2) { return expr_t{e1, e2, op_t::minus}; }

    inline expr_t operator*(const expr_t &e1, const expr_t &e2) { return expr_t{e1, e2, op_t::mul}; }

    inline expr_t operator/(const expr_t &e1, const expr_t &e2) { return expr_t{e1, e2, op_t::div}; }

    inline expr_t operator<<=(const var_t &v, const expr_t &e) { return expr_t{v, e, op_t::assign}; }

    inline expr_t operator+=(const var_t &v, const expr_t &e) { return expr_t{v, e, op_t::plus}; }

    inline expr_t operator-=(const var_t &v, const expr_t &e) { return expr_t{v, e, op_t::minus}; }
}

#endif // INCLUDE_ALGEBRA_HPP
