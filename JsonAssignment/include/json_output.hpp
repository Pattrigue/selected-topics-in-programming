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
    
    bool first = true;
    
    json_ostream(std::ostream& os) : os(os) {
        os << "{";
    }
    
    /** Overload the << operator for boolean values */
    template <Boolean B>
    json_ostream& operator<<(const B& value) {
        os << (value ? "true" : "false");
        return *this;
    }

    /** Overload the << operator for number values */
    template <Number N>
    json_ostream& operator<<(const N& value) {
        os << value;
        return *this;
    }

    /** Overload the << operator for string values */
    template <String S>
    json_ostream& operator<<(const S& value) {
        // TODO: do not put quotes around special values in a more elegant way
        if (value == ":" || value == "," || value == "{" || value == "}" || value == "[" || value == "]" || value == "true" || value == "false" || value == "null") {
            os << value;
            return *this;
        }
        
        os << '"' << value << '"';
        return *this;
    }

    /** Overload the << operator for container values */
    template <Container C>
    json_ostream& operator<<(const C& value) {
        os << '[';

        for (auto it = value.begin(); it != value.end(); ++it) {
            if (it != value.begin()) {
                os << ',';
            }
            
            os << *it;
        }

        os << ']';
        
        return *this;
    }
    
    void close() {
        os << '}';
    }
};


struct json_writer_t
{
    json_ostream& out;
    
    json_writer_t(json_ostream& out) : out(out) {}
    
    bool first = true;
    
    std::string write_key(const std::string& name) {
        if (!first) {
            out.os << ',';
        }
        
        first = false;
        
        return name;
    }
    
    template <typename Data>
    void visit(const std::string& key, const Data& value) {
        value.accept(*this);
        out.close();
    }
    
    // write JSON null
    void visit(const std::string& key, std::nullptr_t) {
         out << write_key(key) << ":null";
    }

    // write JSON boolean
    template <Boolean B>
    void visit(const std::string& key, const B& value) {
        out << write_key(key) << ":" << value;
    }

    // write JSON number
    template <Number N>
    void visit(const std::string& key, const N& value) {
        out << write_key(key) << ":" << value;
    }

    // write JSON string
    template <String S>
    void visit(const std::string& key, const S& value) {
        out << write_key(key) << ":" << '"';
        
        for (char c : value) {
            switch (c) {
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
    void visit(const std::string& key, const T& value) {
        out << write_key(key) << ':' << '[';
        
        for (const auto& item : value) {
            if (&item != &value.front()) {
                out << ',';
            }
            
            out << item;
        }
        
        out << ']';
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
