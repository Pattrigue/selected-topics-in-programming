#ifndef STATIC_VISITOR_JSON_OUTPUT_HPP
#define STATIC_VISITOR_JSON_OUTPUT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include "meta.hpp"


struct json_ostream
{
    std::ostream& os;
    
    void open() { os << '{'; }

    void close() { os << '}'; }
    
    /** overload the << operator for boolean values */
    json_ostream& operator<<(const bool& value) {
        os << (value ? "true" : "false");
        return *this;
    }

    /** overload the << operator for number values */
    json_ostream& operator<<(const int& value) {
        os << value;
        return *this;
    }
    
    json_ostream& operator<<(const double& value) {
        os << value;
        return *this;
    }
    
    /** overload the << operator for char values */
    json_ostream& operator<<(const char& value) {
        os << value;
        return *this;
    }

    /** overload the << operator for string values */
    json_ostream& operator<<(const char* value) {
        return operator<<(std::string_view{value});
    }
    
    json_ostream& operator<<(const std::string& value) {
        return operator<<(std::string_view{value});
    }
    
    json_ostream& operator<<(const std::string_view & value) {
        static const std::unordered_set<std::string_view> special_chars = { 
            ":", ",", "{", "}", "[", "]", "true", "false", "null" 
        };
        
        if (special_chars.find(value) != special_chars.end()) {
            os << value;
        } else {
            os << std::quoted(value);
        }

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
};


struct json_writer_t
{
    json_ostream& out;
    
    json_writer_t(json_ostream& out) : out(out) {}
    
    bool isFirst = true;
    
    /** Helper function to write keys so that commas are added between fields, but not before the isFirst one */
    json_ostream& write_key(const std::string& key) {
        if (!isFirst) {
            out.os << ',';
        }

        isFirst = false;
        return out << key;
    }

    /** the main driver method for writing JSON */
    template <typename Data>
    void visit(const std::string& key, const Data& value) {
        if (!key.empty()) {
            write_key(key) << ":";
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
        write_key(key) << ":null";
    }

    /** write JSON boolean */
    template <Boolean B>
    void visit(const std::string& key, const B& value) {
        write_key(key) << ":" << value;
    }

    /** write JSON number */
    template <Number N>
    void visit(const std::string& key, const N& value) {
        write_key(key) << ":" << value;
    }

    /** write JSON string */
    template <String S>
    void visit(const std::string& key, const S& value) {
        write_key(key) << ":" << value;
    }

    /** write JSON container */
    template <Container T>
    void visit(const std::string& key, const T& value) {
        write_key(key) << ":" << value;
    }
};


template <typename T>
json_ostream& operator<<(json_ostream& j, const T& value) {
    json_writer_t writer(j);
    writer.visit("", value);
    return j;
}

template <typename T>
json_ostream& operator<<(json_ostream&& j, const T& value) {
    return j << value;
}


#endif  // STATIC_VISITOR_JSON_OUTPUT_HPP
