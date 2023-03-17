#ifndef STATIC_VISITOR_JSON_INPUT_HPP
#define STATIC_VISITOR_JSON_INPUT_HPP

#include <iostream>
#include <iomanip>
#include <vector>

/** TODO: implement json_istream adapter with json input operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 * Parsing should follow the type structure rather than the content of the input stream.
 * Visitor parsing may depend on the order of fields, which is OK for this exercise.
 */

struct json_istream
{
    std::istream& is;

    /** override the >> operator for string values */
    json_istream& operator>>(std::string& value) {
        is >> std::quoted(value);
        return *this;
    }

    /** overload the >> operator for boolean values */
    json_istream& operator>>(bool& value) {
        std::string input;
        is >> input;

        if (input == "true") {
            value = true;
        } else if (input == "false") {
            value = false;
        } else {
//            throw std::runtime_error("Invalid boolean value.");
        }

        return *this;
    }

    /** overload the >> operator for number values */
    json_istream& operator>>(int& value) {
        is >> value;
        return *this;
    }

    json_istream& operator>>(double& value) {
        is >> value;
        return *this;
    }

    /** overload the >> operator for container values */
    template <typename T>
    json_istream& operator>>(std::vector<T>& value) {
        char c;
        is >> c;

        if (c != '[') {
//            throw std::runtime_error("Expected '[' character.");
        }

        value.clear();
        is >> c;

        if (c != ']') {
            is.putback(c);

            T first_value;
            is >> first_value;

            value.push_back(first_value);

            while (is >> c) {
                if (c == ',') {
                    T next_value;
                    is >> next_value;
                    value.push_back(next_value);
                } else if (c == ']') {
                    break;
                } else {
//                    throw std::runtime_error("Expected ',' or ']' character.");
                }
            }
        }

        return *this;
    }
};


/** Visitor pattern support for reading JSON */
struct json_reader_t
{
    json_istream& is;
    
    explicit json_reader_t(json_istream& stream) : is(stream) {}

    template <typename Data>
    void visit(const std::string& name, Data& value) {
        is >> value;
    }

    void visit(const std::string& name, bool& value) {
        is >> value;
    }

    void visit(const std::string& name, int& value) {
        is >> value;
    }

    void visit(const std::string& name, double& value) {
        is >> value;
    }

    void visit(const std::string& name, std::string& value) {
        is >> value;
    }

    template <typename T>
    void visit(const std::string& name, std::vector<T>& value) {
        is >> value;
    }
};

template <typename T>
json_reader_t& operator>>(json_reader_t& j, const T& value) {
    j.visit("", value);
    return j;
}

template <typename T>
json_istream& operator>>(json_istream& j, T& value) {
    json_reader_t reader{j};
    value.accept(reader);

    return j;
}

/** Helper for rvalue reference */
template <typename T>
json_istream&& operator>>(json_istream&& j, T& value)
{
    return std::move(j >> value);
}

#endif // STATIC_VISITOR_JSON_INPUT_HPP