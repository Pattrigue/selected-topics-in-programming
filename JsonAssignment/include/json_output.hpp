#ifndef STATIC_VISITOR_JSON_OUTPUT_HPP
#define STATIC_VISITOR_JSON_OUTPUT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "meta.hpp"

/** TODO: implement json_ostream adapter with json output operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 */
struct json_ostream
{
    std::ostream& os;

    /** Overload the << operator for boolean values */
    template <Boolean B>
    void operator<<(const B& value) {
        os << (value ? "true" : "false");
    }

    /** Overload the << operator for number values */
    template <Number N>
    void operator<<(const N& value) {
        os << value;
    }

    /** Overload the << operator for string values */
    template <String S>
    void operator<<(const S& value) {
        os << '"' << value << '"';
    }

    /** Overload the << operator for container values */
    template <Container C>
    void operator<<(const C& value) {
        os << '[';

        for (auto it = value.begin(); it != value.end(); ++it)
        {
            if (it != value.begin()) {
                os << ',';
            }
            
            os << *it;
        }

        os << ']';
    }
};


struct json_writer_t
{
    json_ostream& out;

    json_writer_t(json_ostream& out) : out(out) {}

    // write JSON null
    void visit(const std::string& name, std::nullptr_t) {
        out << "null";
    }

    // write JSON boolean
    template <Boolean B>
    void visit(const std::string& name, const B& value) {
        out << (value ? "true" : "false");
    }

    // write JSON number
    template <Number N>
    void visit(const std::string& name, const N& value) {
        out << value;
    }

    // write JSON string
    template <String S>
    void visit(const std::string& name, const S& value) {
        out << '"';
        
        for (char c : value)
        {
            switch (c)
            {
                case '\"': out << "\\\""; break;
                case '\\': out << "\\\\"; break;
                case '\b': out << "\\b"; break;
                case '\f': out << "\\f"; break;
                case '\n': out << "\\n"; break;
                case '\r': out << "\\r"; break;
                case '\t': out << "\\t"; break;
                default: out << c; break;
            }
        }
        out << '"';
    }

    // write JSON container
    template <Container T>
    void visit(const std::string& name, const T& value) {
        out << '[';
        
        for (const auto& item : value) {
            if (&item != &value.front()) {
                out << ',';
            }
            
            out << item;
        }
        
        out << ']';
    }

    // write JSON aggregate
    template <typename T>
    void visit(const std::string& name, const T& value) {
        out << '{';
        
        for_each_field(value, [&](auto&& field_name, auto&& field_value) {
            if (&field_value != &value)
            {
                out << ',';
            }
            
            visit(field_name, field_value);
            out << ':';
            visit(field_name, field_value);
        });
        
        out << '}';
    }
};


template <typename T>
json_writer_t& operator<<(json_writer_t& j, const T& value)
{
    j.visit("", value);
    return j;
}

template <typename T>
json_writer_t& operator<<(json_writer_t&& j, const T& value)
{
    return j << value;
}


#endif  // STATIC_VISITOR_JSON_OUTPUT_HPP
