#include <iostream>
#include <vector>
#include <string>


// Define a helper template that will be used to detect whether a type is a container.
template <typename T, typename = void>
struct is_container : std::false_type {};

// Specialize the helper template for types that have a "begin" and "end" member function.
template <typename T>
struct is_container<T,
        std::void_t<
                decltype(std::begin(std::declval<T>())),
                decltype(std::end(std::declval<T>()))>
        >
        : std::true_type {};


template<typename T>
// use std::remove_cvref to remove const, volatile, and reference qualifiers from the type
constexpr bool is_string_v = std::is_same_v<std::remove_cvref_t<T>, std::basic_string<char>> ||
                             (std::is_same_v<std::remove_cvref_t<T>, T> &&
                              std::is_same_v<typename T::value_type, char> &&
                              !std::is_same_v<std::remove_cvref_t<T>, const char*>);

//constexpr auto is_string_v = is_container<T>::value && (std::is_same_v<typename T::value_type, char> || std::is_same_v<typename T::value_type, const char>);


template<typename T>
constexpr auto is_non_string_container = is_container<T>::value && !is_string_v<T>;

//template <typename T, typename = std::enable_if_t<is_container<T>::value>>
//template <typename T, typename = std::enable_if<is_container<T>::value>>


template <typename T>
concept Container = is_container<T>::value;

template <Container C>
std::ostream& operator<<(std::ostream& os, const C& c) {
    auto b = c.begin();
    auto e = c.end();
    
    os << "{";
    
    if (b != e) {
        os << *b;
        
        while (++b != e) {
            os << "," << *b;
        }
    }
    
    return os << "}";
}


// create a function using is_string to check if the type is a string
template <typename T, typename = std::enable_if_t<is_string_v<T>>>
void function_that_can_only_be_called_on_strings(const T& s) {
    std::cout << "function_that_can_only_be_called_on_strings called with " << s << std::endl;
}


// create a function using is_non_string_container to check if the type is a container
template <typename T, typename = std::enable_if_t<is_non_string_container<T>>>
void function_on_non_string_containers(const T& s) {
    std::cout << "function_on_non_string_containers called with " << s << std::endl;
}


int main(){
    std::cout << std::vector{1,2,3} << std::endl; // should print "{1,2,3}"
    std::cout << std::vector{2.7,3.14} << std::endl; // should print "{2.7,3.14}"
    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl;
    
    auto vec_of_strings = std::vector{"hello", "world"};
    auto vec_of_chars = std::vector{'a', 'b', 'c'};
    auto vec_of_ints = std::vector{1, 2, 3};

    std::cout << vec_of_strings << std::endl; // should print "{hello,world}"
    
    function_that_can_only_be_called_on_strings(vec_of_chars); // should compile
    function_that_can_only_be_called_on_strings(vec_of_ints); // should not compile
    
    function_on_non_string_containers(vec_of_chars); // should not compile
    function_on_non_string_containers(vec_of_ints); // should compile
    
    return 0;
}
