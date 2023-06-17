#include <iostream>

class Line {
    double m_x;
    double m_y;
    
public:
    // Default constructor
    Line(double x, double y) 
        : m_x(x), m_y(y) {
        std::cout << "Default constructor called." << std::endl;
    }
    
    // Copy constructor
    Line(const Line& other)
        : m_x(other.m_x), m_y(other.m_y) {
        std::cout << "Copy constructor called." << std::endl;
    }
        
    
    // Copy assignment constructor
    Line& operator=(const Line& other) {
        std::cout << "Copy assignment constructor called." << std::endl;
        
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
        }
        
        return *this;
    }
        
    // Move constructor
    Line(Line&& other)
        : m_x(other.m_x), m_y(other.m_y) {
        std::cout << "Move constructor called." << std::endl;
    }
    
    // Move assignment constructor
    Line& operator=(Line&& other) {
        std::cout << "Move assignment constructor called." << std::endl;
        
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
        }
        
        return *this;
    }
};

int main() {
    Line coord1 {4.20, 69.0 }; // Default constructor
    Line coord2 { 69.0, 4.20 }; // Default constructor
    
    Line copy = coord1; // Copy constructor
    copy = coord2; // Copy assignment constructor
    
    Line move = Line(std::move(coord1)); // Move constructor
    move = std::move(coord2); // Move assignment constructor
    
    return 0;
}
