#include "power.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

auto benchmark = [](std::string name, size_t iterations, auto&& f) {
  auto start = std::chrono::high_resolution_clock::now();
  
  for (size_t i = 0; i < iterations; ++i) {
	  f();
  }
  
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  
  std::cout << duration << " ms to execute " << name << " " << iterations << " times." << std::endl;
};

TEST_CASE("Integer power - runtime and compile-time")
{
	SUBCASE("Runtime power")
	{
		REQUIRE(power(2, 0) == 1);
		REQUIRE(power(2, 1) == 2);
		REQUIRE(power(2, 2) == 4);
		REQUIRE(power(2, 3) == 8);
		REQUIRE(power(5, 5) == 3125);
	}

	SUBCASE("Compile-time power")
	{
		REQUIRE(Power<2, 2>::value == 4);
		REQUIRE(Power<2, 3>::value == 8);
		REQUIRE(Power<5, 5>::value == 3125);
	}
	
	SUBCASE("Benchmark") 
	{
		// benchmark compile-time power vs. runtime power
		constexpr int iterations = 1000000;
		
		benchmark("runtime power", iterations, []() {
			power(2, 3);
		});
		
		benchmark("compile-time Power", iterations, []() {
			Power<2, 3>::value;
		});
		
		benchmark("std::pow", iterations, []() {
			std::pow(2, 3);
		});
	}
}