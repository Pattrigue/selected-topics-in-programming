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
    
    /** overload the << operator for boolean values */
    template <Boolean B>
    json_ostream& operator<<(const B& value) {
        os << (value ? "true" : "false");
        return *this;
    }

    /** overload the << operator for number values */
    template <Number N>
    json_ostream& operator<<(const N& value) {
        os << value;
        return *this;
    }

    /** overload the << operator for string values */
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

    /** overload the << operator for container values */
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
    
    void open() {
        os << '{';
    }
    
    void close() {
        os << '}';
    }
};


struct json_writer_t
{
    json_ostream& out;
    
    json_writer_t(json_ostream& out) : out(out) {}
    
    bool isFirst = true;
    
    /** Helper function to write keys so that commas are added between fields, but not before the isFirst one */
    std::string write_key(const std::string& key) {
        if (!isFirst) {
            out.os << ',';
        }

        isFirst = false;
        
        return key;
    }

    /** the main driver method for writing JSON */
    template <typename Data>
    void visit(const std::string& key, const Data& value) {
        if (!key.empty()) {
            out << write_key(key) << ":";
        }
        
        /** save the isFirst flag to handle nested objects */
        bool was_first = isFirst;

        isFirst = true;
        
        out.open();
        value.accept(*this);
        out.close();
        
        /** restore the isFirst flag */
        isFirst = was_first;
    }
    
    /** write JSON null */
    void visit(const std::string& key, std::nullptr_t) {
         out << write_key(key) << ":null";
    }

    /** write JSON boolean */
    template <Boolean B>
    void visit(const std::string& key, const B& value) {
        out << write_key(key) << ":" << value;
    }

    /** write JSON number */
    template <Number N>
    void visit(const std::string& key, const N& value) {
        out << write_key(key) << ":" << value;
    }

    /** write JSON string */
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

    /** write JSON container */
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
