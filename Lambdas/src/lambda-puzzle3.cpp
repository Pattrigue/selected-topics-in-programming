/**
 * Purpose: exercise lambda expressions with STL algorithms.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#include <doctest.h>
#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <iterator>

static auto gen = std::mt19937{std::random_device{}()};
static auto dist = std::uniform_int_distribution<int>{0, 100};


void fill_with_data(std::vector<int>& data, size_t count)
{
    std::generate_n(std::back_inserter(data), count, [&]() {
        return dist(gen);
    });
    
//    for (auto i=0u; i<count; ++i)
//		data.push_back(dist(gen));
}

void print_data(std::ostream& os, const std::vector<int>& data)
{
    std::copy(data.begin(), data.end(), std::ostream_iterator<int>(os, " "));
    
//    for (auto&& d: data)
//		os << d << ' ';
//    os << '\n';
}

int compute_sum(const std::vector<int>& data)
{
    /** TODO: use accumulate instead */
    return std::accumulate(data.begin(), data.end(), 0, [](int acc, int value) {
       return acc += value;
    });
//    auto res = 0;
//    for (auto&& d: data)
//		res += d;

//    return res;
}

std::string concatenate(const std::vector<int>& data)
{
    return std::accumulate(data.begin(), data.end(), std::string{}, [](std::string str, int b) {
        return  str + std::to_string(b);
    });

//    auto res = std::string{};
//    for (auto&& d: data)
//		res += std::to_string(d);
//
//    return res;
}

size_t odd_count(const std::vector<int>& data)
{
    return std::count_if(data.begin(), data.end(), [](int i){
        return i % 2 == 1; 
    });
    
//    auto count = 0u;
//    
//    for (auto&& d: data)
//		if (d % 2 == 1)
//			++count;
//    
//    return count;
}

std::vector<std::string> stringify(const std::vector<int>& data)
{
    auto res = std::vector<std::string>{};
    std::transform(std::begin(data), std::end(data), std::back_inserter(res), [](auto&& value) {
        return std::to_string(value);
    });

//    for (auto&& d: data)
//		res.push_back(std::to_string(d));
    
    return res;
}

std::vector<std::string> compute_sorted(const std::vector<std::string>& data)
{
    // sorting implementation of decreasing alphabetical order
    auto res = data;
    std::sort(std::begin(res), std::end(res), [](auto&& a, auto&& b) { return a < b; });
    
    return res;
}


std::vector<int> squares(const std::vector<int>& data)
{
    // compute square of each input element
    auto res = std::vector<int>{};
    std::transform(std::begin(data), std::end(data), std::back_inserter(res),
                   [](auto&& d) { return d * d; });
    
    return res;
}

TEST_CASE("Lambda puzzle3")
{
    auto data = std::vector<int>{};
    fill_with_data(data, 20);
    
    CHECK(data.size() == 20);
    
    SUBCASE("print_data")
    {
        std::cout << "data: ";
        print_data(std::cout, data);
        
        std::stringstream ss;

        print_data(ss, data);

        // check that each value in ss is a value in data
        for (auto i : data) {
            auto str = std::to_string(i);
            CHECK(ss.str().find(str) != std::string::npos);
        }
    }
    
    SUBCASE("compute_sum")
    {
        std::cout << "sum: " << compute_sum(data) << std::endl;

        auto sum = 0;

        for (auto i : data)
            sum += i;

        CHECK(sum == compute_sum(data));
    }
    
    SUBCASE("concat")
    {
        std::cout << "concat: " << concatenate(data) << std::endl;

        auto concat = std::string{};

        for (auto i : data)
            concat += std::to_string(i);

        CHECK(concat == concatenate(data));
    }
    
    SUBCASE("odd_count")
    {
        std::cout << "odd count: " << odd_count(data) << std::endl;

        auto num_odd = 0;

        for (auto i : data)
            if (i % 2 == 1)
                num_odd++;

        CHECK(num_odd == odd_count(data));
    }
    
    SUBCASE("stringify")
    {
        auto data_str = stringify(data);

        CHECK(data_str.size() == data.size());

        for (int i = 0; i < data.size(); i++) {
            CHECK(data_str[i] == std::to_string(data[i]));
        }
    }
    
    SUBCASE("compute_sorted")
    {
        auto data_str = stringify(data);
        auto sorted_str = compute_sorted(data_str);
        auto std_sorted_str = data_str;
        std::sort(std_sorted_str.begin(), std_sorted_str.end());

        CHECK(sorted_str == std_sorted_str);
    }
    
    // TODO: make print_data a function template, so that the following is accepted:
    //print_data(std::cout, sorted_str);
    SUBCASE("squares") {
        std::cout << "squares: ";
        print_data(std::cout, squares(data));

        auto squared_data = std::vector<int>{};

        for (auto i : data)
            squared_data.push_back(i * i);

        CHECK(squared_data == squares(data));
    }
}
