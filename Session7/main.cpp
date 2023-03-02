#include <iostream>
#include <vector>

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


int main() {
    std::vector<int> v = {1, 2, 3};

    print(v);
    
    std::cout << v << std::endl;
    std::cout << std::vector{1, 2, 3} << std::endl; // should still print "{1,2,3}"
    std::cout << std::vector{2.7, 3.14} << std::endl; // should print "{2.7,3.14}"
    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl; // should print "{{hello,template}{world}}"   
    
    return 0;
}
