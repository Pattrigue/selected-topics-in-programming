#ifndef TEMPLATES_POWER_HPP
#define TEMPLATES_POWER_HPP

#include <cstddef>

template <typename T>
T power(T number, std::size_t p)
{
	if (p == 0)
		return 1;
	if (p == 1)
		return number;
	T res = power(number, p/2);
	res *= res;
	if (p%2 == 1)
		res *= number;
	return res;
}

// compile-time power implementation
template <std::size_t Base, std::size_t Exp>
struct Power {
	static constexpr std::size_t value = Base * Power<Base, Exp - 1>::value;
};

template <std::size_t Base>
struct Power<Base, 0> {
	static constexpr std::size_t value = 1;
};

#endif	// TEMPLATES_POWER_HPP
