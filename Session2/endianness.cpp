#include <iostream>
#include <bitset>

union Data {
    float f;
    unsigned int i;
    char s[4];
};

void determine_endianness() {
    // this makes the char[4] array become 4, 3, 2, and 1 or 1, 2, 3, 4 (depending on endianness)
    Data data = {.i = 0x01020304}; 

    std::cout << "Character array: ";
    for (char i: data.s) {
        std::cout << (int) i << " ";
    }
    std::cout << std::endl;

    if (data.s[0] == 1 && data.s[1] == 2 && data.s[2] == 3 && data.s[3] == 4) {
        // big-endian would represent 0x01020304 in the order 1 2 3 4
        // (the most significant byte of the data is placed at the byte with the lowest address)
        std::cout << "This machine uses big-endian." << std::endl << std::endl;
    } else if (data.s[0] == 4 && data.s[1] == 3 && data.s[2] == 2 && data.s[3] == 1) {
        // small-endian would represent 0x01020304 in the order 4 3 2 1
        // (the least significant byte of the data is placed at the byte with the lowest address)
        std::cout << "This machine uses little-endian." << std::endl << std::endl;
    } else {
        std::cout << "Unable to determine endianness." << std::endl << std::endl;
    }

    // for more on Endianness: https://chortle.ccsu.edu/assemblytutorial/Chapter-15/ass15_3.html
}

void extract_IEEE_bits(std::bitset<32> bits) {
    std::cout << "Sign: " << bits[31] << std::endl;
    std::cout << "Exponent: ";
    
    for (int i = 30; i > 22; i--) {
        std::cout << bits[i];
    }
    
    std::cout << std::endl;
    std::cout << "Mantissa: ";
    
    for (int i = 22; i >= 0; i--) { 
        std::cout << bits[i];
    }
    
    std::cout << std::endl << std::endl;
}

void reinterpret_float_as_unsigned_int() {
    float values[] = { 1.0f, 2.0f, 4.0f, 8.0f };

    for (const float &value: values) {
        Data data = { .f = value };
        auto bits = std::bitset<32>(data.i);
        
        std::cout 
        << "Float value = " << data.f 
        << ", unsigned integer value = " << data.i 
        << ", unsigned integer bits = " << bits
        << std::endl;

        extract_IEEE_bits(bits);
    }
}