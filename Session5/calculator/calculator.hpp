#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace calculator {
    /** Type to capture the state of entire calculator (one number per variable): */
    using state_t = std::vector<double>;

    /** Forward declarations to get around circular dependencies: */
    struct expr_t;
    
    enum op_t {
        plus, minus, mul, div, assign
    } op;

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

        [[nodiscard]] size_t id() const {
            return m_id;
        }

        /** evaluates an assignment to a given expression and returns the resulting value */
        double operator()(state_t &, const expr_t &) const;

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
            double res = (*term)(s);
            
            switch (op) {
                case plus:
                    s[var->id()] += res;
                    break;
                case minus:
                    s[var->id()] -= res;
                    break;
                case mul:
                    s[var->id()] *= res;
                    break;
                case div:
                    s[var->id()] /= res;
                    break;
                case assign:
                    s[var->id()] = res;
                    break;
            }
            
            return res;
        }
    };
    
    class unary_t : public term_t {
        std::shared_ptr<term_t> term;
        op_t op;
    public:
        unary_t(std::shared_ptr<term_t> term, op_t op) 
            : term{std::move(term)}, op{op} {} 

        double operator()(state_t &s) const override {
            double res = (*term)(s);
            
            switch (op) {
                case plus:
                    return res;
                case minus:
                    return -res;
                default:
                    throw std::logic_error{"invalid unary operator"};
            }
        }
    };
    
    class binary_t : public term_t {
        std::shared_ptr<term_t> term1;
        std::shared_ptr<term_t> term2;
        op_t op;
    public:
        binary_t(std::shared_ptr<term_t> term1, std::shared_ptr<term_t> term2, op_t op)
                : term1{std::move(term1)}, term2{std::move(term2)}, op{op} {}

        double operator()(state_t &s) const override {
            double res1 = (*term1)(s);
            double res2 = (*term2)(s);

            switch (op) {
                case plus:
                    return res1 + res2;
                case minus:
                    return res1 - res2;
                case mul:
                    return res1 * res2;
                case div:
                    return res1 / res2;
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
        std::unique_ptr<var_t> var;
        std::vector<std::unique_ptr<expr_t>> operands;

        enum op_t_old {
            plus, minus, add, sub, mul, div, assign
        } op_old;

        expr_t(const expr_t &other) {
            *this = other;
        }

        expr_t &operator=(const expr_t &other) {
            op_old = other.op_old;
            var = other.var ? std::make_unique<var_t>(*other.var) : nullptr;

            operands.resize(other.operands.size());

            std::transform(other.operands.begin(), other.operands.end(), operands.begin(),
                           [](const auto &ptr) {
                               return std::make_unique<expr_t>(*ptr);
                           });

            return *this;
        }

        expr_t(expr_t &&other) noexcept = default;

        expr_t &operator=(expr_t &&other) noexcept = default;

        ~expr_t() noexcept = default;

        expr_t(const var_t &v, op_t_old op_old = plus)
                : var{std::make_unique<var_t>(v)}, op_old{op_old} {}

        expr_t(const var_t &v, const expr_t &e)
                : var{std::make_unique<var_t>(v)}, operands(1), op_old{assign} {
            operands[0] = std::make_unique<expr_t>(e);
        }

        expr_t(const expr_t &e, op_t_old op_old) : operands(1), op_old{op_old} {
            operands[0] = std::make_unique<expr_t>(e);
        }

        expr_t(const expr_t &e1, const expr_t &e2, op_t_old op_old)
                : operands(2), op_old{op_old} {
            operands[0] = std::make_unique<expr_t>(e1);
            operands[1] = std::make_unique<expr_t>(e2);
        }

        double operator()(state_t &s) const {
            if (var) {
                auto &v = *var;

                switch (op_old) {
                    case expr_t::plus:
                        return v(s);
                    case expr_t::minus:
                        return -v(s);
                    case expr_t::assign:
                        if (operands.empty()) {
                            throw std::logic_error{"missing expression to evaluate"};
                        }

                        return v(s, *operands[0]);
                    default:
                        throw std::logic_error{"unsupported operation over a variable"};
                }
            } else {
                auto &e1 = *operands[0];

                switch (op_old) {
                    case expr_t::plus:
                        if (operands.empty()) {
                            throw std::logic_error{"bug: missing an operand for unary +"};
                        }

                        return e1(s);
                    case expr_t::minus:
                        if (operands.empty()) {
                            throw std::logic_error{"bug: missing an operand for unary -"};
                        }

                        return -e1(s);
                    case expr_t::add: {
                        if (operands.size() != 2) {
                            throw std::logic_error{"bug: expecting two operands for binary +"};
                        }

                        auto &e2 = *operands[1];

                        return e1(s) + e2(s);
                    }
                    case expr_t::sub: {
                        if (operands.size() != 2) {
                            throw std::logic_error{"bug: expecting two operands for binary -"};
                        }

                        auto &e2 = *operands[1];

                        return e1(s) - e2(s);
                    }
                    case expr_t::mul: {
                        if (operands.size() != 2) {
                            throw std::logic_error{"bug: expecting two operands for binary *"};
                        }

                        auto &e2 = *operands[1];

                        return e1(s) * e2(s);
                    }
                    case expr_t::div: {
                        if (operands.size() != 2) {
                            throw std::logic_error{"bug: expecting two operands for binary /"};
                        }

                        auto &e2 = *operands[1];

                        if (e2(s) == 0) {
                            throw std::logic_error{"division by zero"};
                        }

                        return e1(s) / e2(s);
                    }
                    default:
                        throw std::logic_error{"not implemented"};
                }
            }
        }
    };

    /** assignment operation */
    inline double var_t::operator()(state_t &s, const expr_t &e) const {
        return s[m_id] = e(s);
    }

    /** unary operators: */
    inline expr_t operator+(const expr_t &e) {
        return expr_t{e, expr_t::plus};
    }

    inline expr_t operator-(const expr_t &e) {
        return expr_t{e, expr_t::minus};
    }

    /** binary operators: */
    inline expr_t operator+(const expr_t &e1, const expr_t &e2) {
        return expr_t{e1, e2, expr_t::add};
    }

    inline expr_t operator-(const expr_t &e1, const expr_t &e2) {
        return expr_t{e1, e2, expr_t::sub};
    }

    inline expr_t operator*(const expr_t &e1, const expr_t &e2) {
        return expr_t{e1, e2, expr_t::mul};
    }

    inline expr_t operator/(const expr_t &e1, const expr_t &e2) {
        return expr_t{e1, e2, expr_t::div};
    }

    inline expr_t operator<<=(const var_t &v, const expr_t &e) {
        return expr_t{v, e};
    }
}

#endif // INCLUDE_ALGEBRA_HPP

