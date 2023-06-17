#include <doctest/doctest.h>
#include "SymbolTable.hpp"

using namespace StochSimLib;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"

/** Tests the SymbolTable class. 
 * Fulfills part of requirement 9:
 * "Implement unit tests (e.g. test symbol table methods and pretty-printing of reaction rules)". */

TEST_SUITE("SymbolTable Test Suite") {
    TEST_CASE("SymbolTable - Adding and Retrieving") {
        SymbolTable<int> table;

        table.add("a", 1);
        table.add("b", 2);
        table.add("c", 3);

        CHECK(table["a"] == 1);
        CHECK(table["b"] == 2);
        CHECK(table["c"] == 3);
    }

    TEST_CASE("SymbolTable - Modifying") {
        SymbolTable<int> table;

        table.add("a", 1);
        table.add("b", 2);
        table.add("c", 3);

        table["a"] = 4;
        table["b"] = 5;
        table["c"] = 6;

        CHECK(table["a"] == 4);
        CHECK(table["b"] == 5);
        CHECK(table["c"] == 6);
    }

    TEST_CASE("SymbolTable - Removing") {
        SymbolTable<int> table;

        table.add("a", 1);
        table.add("b", 2);
        table.add("c", 3);

        table.remove("a");
        table.remove("b");
        table.remove("c");

        CHECK(table.tryGet("a") == std::nullopt);
        CHECK(table.tryGet("b") == std::nullopt);
        CHECK(table.tryGet("c") == std::nullopt);
    }

    TEST_CASE("SymbolTable - Size Check") {
        SymbolTable<int> table;

        table.add("a", 1);
        table.add("b", 2);
        table.add("c", 3);
        
        CHECK(table.size() == 3);

        table.remove("a");
        table.remove("b");
        table.remove("c");

        CHECK(table.size() == 0);
    }

    TEST_CASE("SymbolTable - Duplicate Add") {
        SymbolTable<int> table;

        table.add("a", 1);
        
        CHECK_THROWS_AS(table.add("a", 2), std::runtime_error);
    }

    TEST_CASE("SymbolTable - Nonexistent Remove") {
        SymbolTable<int> table;

        CHECK_NOTHROW(table.remove("a"));
    }

    TEST_CASE("SymbolTable - Nonexistent Subscript") {
        SymbolTable<int> table;

        CHECK_THROWS_AS(table["a"], std::runtime_error);
    }

    TEST_CASE("SymbolTable - Add and Retrieve Shared Ptr") {
        SymbolTable<std::shared_ptr<int>> table;
        
        auto ptr = std::make_shared<int>(1);
        auto ptr_copy = ptr; // copy of the shared_ptr for comparison

        table.add("a", std::move(ptr));

        // Compare the values that the shared_ptrs point to
        CHECK(*(table["a"]) == *ptr_copy);

        // Compare the shared_ptrs directly (the addresses they hold, not the integers)
        CHECK(table["a"] == ptr_copy);
    }

    TEST_CASE("SymbolTable - Iteration") {
        SymbolTable<int> table;

        table.add("a", 1);
        table.add("b", 2);
        table.add("c", 3);

        int sum = 0;
        
        for(auto& [key, value] : table) {
            sum += *value;
        }

        CHECK(sum == 6);
    }
}

#pragma GCC diagnostic pop