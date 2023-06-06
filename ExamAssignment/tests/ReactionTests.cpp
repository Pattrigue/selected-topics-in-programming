#include <doctest/doctest.h>
#include "Reaction.h"
#include "Species.h"

using namespace StochSimLib;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"

/** Tests the Reaction class pretty-printing. 
 * Fulfills part of requirement 9:
 * "Implement unit tests (e.g. test symbol table methods and pretty-printing of reaction rules)". */

TEST_CASE("Test pretty printing") {
    Reaction reaction;
    reaction.addReactant(std::make_shared<Species>("A", 1));
    reaction.addReactant(std::make_shared<Species>("C", 1));
    reaction.addProduct(std::make_shared<Species>("B", 0));
    reaction.addProduct(std::make_shared<Species>("C", 0));
    
    reaction.rate = 50.0;
    
    CHECK(reaction.name() == "A + C -> B + C (rate = 50)");
}

#pragma GCC diagnostic pop