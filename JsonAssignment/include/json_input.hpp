#ifndef STATIC_VISITOR_JSON_INPUT_HPP
#define STATIC_VISITOR_JSON_INPUT_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "meta.hpp"

/** TODO: implement json_istream adapter with json input operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 * Parsing should follow the type structure rather than the content of the input stream.
 * Visitor parsing may depend on the order of fields, which is OK for this exercise.
 */
 
struct json_reader_t;


template<typename T, typename = void>
struct has_accept : std::false_type {};

template<typename T>
struct has_accept<T, std::void_t<decltype(std::declval<T>().accept(std::declval<json_reader_t&>()))>> : std::true_type {};

template<typename T>
inline constexpr bool has_accept_v = has_accept<T>::value;


struct json_istream
{
    std::istream& is;
    
    void readBoolean(const std::string& key, bool& value) {
        while (is.good()) {
            char c = is.get();

            if (c == '\"') {
                std::string fieldName;
                std::getline(is, fieldName, '\"');

                if (fieldName == key) {
                    is.get(); // consume the ':'
                    is >> std::boolalpha >> value;
                    break;
                }
            }
        }
    }
    
    void readString(const std::string& key, std::string& value) {
        while (is.good()) {
            char c = is.get();

            if (c == '\"') {
                std::string fieldName;
                std::getline(is, fieldName, '\"');

                if (fieldName == key) {
                    is.get(); // consume the ':'
                    is.get(); // consume the '\"'
                    std::getline(is, value, '\"');
                    break;
                }
            }
        }
    }

    void readNumber(const std::string& key, int& value) {
        double d;
        readDouble(key, d);
        value = static_cast<int>(d);
    }
    
    void readDouble(const std::string& key, double& value) {
        while (is.good()) {
            char c = is.get();

            if (c == '\"') {
                std::string fieldName;
                std::getline(is, fieldName, '\"');

                if (fieldName == key) {
                    is.get(); // consume the ':'
                    is >> value;
                    break;
                }
            }
        }
    }
    
    void readContainer(const std::string& key, std::vector<int>& value) {
        while (is.good()) {
            char c = is.get();

            if (c == '\"') {
                std::string fieldName;
                std::getline(is, fieldName, '\"');

                if (fieldName == key) {
                    is.get(); // consume the ':'
                    is.get(); // consume the '['
                    
                    while (is.good() && is.peek() != ']') {
                        int i;
                        is >> i;
                        value.push_back(i);

                        if (is.peek() == ',') {
                            is.get(); // consume the ','
                        }
                    }
                    
                    is.get(); // consume the ']'
                    break;
                }
            }
        }
    }

    auto str() {
        return is.rdbuf();
    }
};


/** Visitor pattern support for reading JSON */
struct json_reader_t
{
    json_istream& in;
    
    /* visitor for the bool type **/
    void visit(const std::string& key, bool& value) {
        in.readBoolean(key, value);
    }
    
    /* visitor for the int type **/
    void visit(const std::string& key, int& value) {
        in.readNumber(key, value);
    }
    
    /* visitor for the double type **/
    void visit(const std::string& key, double& value) {
        in.readDouble(key, value);
    }
    
    /* visitor for the string type **/
    void visit(const std::string& key, std::string& value) {
        in.readString(key, value);
    }
    
    /* visitor for the vector<int> type **/
    void visit(const std::string& key, std::vector<int>& value) {
        in.readContainer(key, value);
    }
};


template <typename T>
json_istream& operator>>(json_istream& j, T& value)
{
    json_reader_t reader{j};

    if constexpr (std::is_same_v<T, bool>) {
        reader.visit("", value); // call bool visitor
    } else if constexpr (std::is_same_v<T, int>) {
        reader.visit("", value); // call int visitor
    } else if constexpr (std::is_same_v<T, double>) {
        reader.visit("", value); // call double visitor
    } else if constexpr (std::is_same_v<T, std::string>) {
        reader.visit("", value); // call string visitor
    } else if constexpr (std::is_same_v<T, std::vector<int>>) {
        reader.visit("", value); // call vector<int> visitor
    } else if constexpr (has_accept_v<T>) {
        value.accept(reader); // call visitor for custom type T (if it has accept() method)
    } else {
        throw std::runtime_error("Unsupported type.");
    }

    return j;
}


/** Helper for rvalue reference */
template <typename T>
json_istream& operator>>(json_istream&& j, T& value)
{
    return j >> value;
}

#endif // STATIC_VISITOR_JSON_INPUT_HPP