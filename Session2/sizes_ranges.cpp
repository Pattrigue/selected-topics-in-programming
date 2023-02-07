#include <iostream>
#include <limits>

void print_sizes_and_ranges() {
    std::cout << "bool: " << sizeof(bool) << " bytes, "
              << "range: [" << std::numeric_limits<bool>::min() << ", "
              << std::numeric_limits<bool>::max() << "]" << std::endl;

    std::cout << "char: " << sizeof(char) << " bytes, "
              << "range: [" << (int) std::numeric_limits<char>::min() << ", "
              << (int) std::numeric_limits<char>::max() << "]" << std::endl;

    std::cout << "signed char: " << sizeof(signed char) << " bytes, "
              << "range: [" << (int) std::numeric_limits<signed char>::min() << ", "
              << (int) std::numeric_limits<signed char>::max() << "]" << std::endl;

    std::cout << "unsigned char: " << sizeof(unsigned char) << " bytes, "
              << "range: [" << (int) std::numeric_limits<unsigned char>::min() << ", "
              << (int) std::numeric_limits<unsigned char>::max() << "]" << std::endl;

    std::cout << "short: " << sizeof(short) << " bytes, "
              << "range: [" << std::numeric_limits<short>::min() << ", "
              << std::numeric_limits<short>::max() << "]" << std::endl;

    std::cout << "unsigned short: " << sizeof(unsigned short) << " bytes, "
              << "range: [" << std::numeric_limits<unsigned short>::min() << ", "
              << std::numeric_limits<unsigned short>::max() << "]" << std::endl;

    std::cout << "int: " << sizeof(int) << " bytes, "
              << "range: [" << std::numeric_limits<int>::min() << ", "
              << std::numeric_limits<int>::max() << "]" << std::endl;

    std::cout << "unsigned int: " << sizeof(unsigned int) << " bytes, "
              << "range: [" << std::numeric_limits<unsigned int>::min() << ", "
              << std::numeric_limits<unsigned int>::max() << "]" << std::endl;

    std::cout << "long: " << sizeof(long) << " bytes, "
              << "range: [" << std::numeric_limits<long>::min() << ", "
              << std::numeric_limits<long>::max() << "]" << std::endl;

    std::cout << "unsigned long: " << sizeof(unsigned long) << " bytes, "
              << "range: [" << std::numeric_limits<unsigned long>::min() << ", "
              << std::numeric_limits<unsigned long>::max() << "]" << std::endl;
}