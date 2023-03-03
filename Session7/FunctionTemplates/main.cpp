#include <iostream>
#include <vector>
#include <list>
#include <iomanip>

void print(const std::vector<int> &v) {
    auto end = v.end() - 1;

    std::cout << "{";
    
    for (const auto &item: v) {
        if (item == *end) {
            std::cout << item;
        } else {
            std::cout << item << ", ";
        }
    }
    
    std::cout << "}" << std::endl;
}

template<class T>
std::ostream& operator <<(std::ostream &os, const std::vector<T> &v) {
    auto end = v.end() - 1;

    os << "{";
    
    for (const auto &item: v) {
        if (item == *end) {
            os << item;
        } else {
            os << item << ", ";
        }
    }
    
    os << "}";

    return os;
}

template<typename C, typename = typename C::value_type>
std::ostream& operator<<(std::ostream &os, const C &container) {
    auto end = std::end(container);

    os << "[";

    for (const auto &item: container) {
        // If item is a char* or a char[], print it with quotes around it using std::quoted
        if constexpr (std::is_same_v<typename C::value_type, char*> || std::is_same_v<typename C::value_type, char[]>) {
            os << std::quoted(item);
        } else {
            os << item;
        }
        
        // Only print a comma if the item is not the last item in the container
        if (item != *std::prev(end)) {
            os << ", ";
        }
    }

    os << "]";
    
    return os;
}


int main() {
    std::vector<int> v = {1, 2, 3};
    char* c_string = "Hello there";

    print(v);
    
    std::cout << v << std::endl;
    std::cout << std::vector{1, 2, 3} << std::endl; // should still print "{1,2,3}"
    std::cout << std::vector{2.7, 3.14} << std::endl; // should print "{2.7,3.14}"
    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl; // should print "{{hello,template}{world}}"   
    
    std::cout << std::list<int> {1, 2, 3, 4, 5} << std::endl;
    std::cout << std::list<char*> {"Hello", "there"} << std::endl;
    
    return 0;
}
