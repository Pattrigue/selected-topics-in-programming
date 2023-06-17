#ifndef STOCHSIMLIB_REACTION_H
#define STOCHSIMLIB_REACTION_H

#include <sstream>
#include <string>
#include <random>
#include "ReactionCompounds.h"

namespace StochSimLib {

    class Reaction {
        ReactionCompounds m_reactants;
        ReactionCompounds m_products;

    public:
        double rate = 0;
        double delay = 0;

        [[nodiscard]] ReactionCompounds &reactants();

        [[nodiscard]] ReactionCompounds &products();

        /** Returns the reaction as a human readable string. 
         * This fulfills part of requirement 2: "Pretty-print the reaction network in a human readable format". */
        [[nodiscard]] std::string name() const;

        void addReactant(const Species &reactant);

        void addProduct(const Species &product);
        
        /** Computes the delay of the reaction using equation 1 from the PDF. 
         * This fulfills part of requirement 4: 
         * "Implement the stochastic simulation of the system using the reaction rules." */
        void computeDelay(std::mt19937 &generator);

        friend std::ostream &operator<<(std::ostream &os, const Reaction &reaction);
    };

    /* Models a reaction where multiple reactants (compounds) form a single product (species). E.g., A + B -> C.
     * This fulfills part of requirement 1: 
     * "Use operator overloading to support the reaction rule typesetting directly in C++ code." */
    Reaction operator>>=(ReactionCompounds &&compounds, const Species &species);

    /* Models a reaction where a single reactant (species) forms multiple products (compounds). E.g., A -> B + C.
     * This fulfills part of requirement 1:
     * "Use operator overloading to support the reaction rule typesetting directly in C++ code." */
    Reaction operator>>=(const Species &species, ReactionCompounds &&compounds);

    /* Models a reaction where multiple reactants (compounds) form multiple products (compounds). E.g., A + B -> C + D.
     * This fulfills part of requirement 1:
     * "Use operator overloading to support the reaction rule typesetting directly in C++ code." */
    Reaction operator>>=(const ReactionCompounds &compoundsL, const ReactionCompounds &compoundsR);

    /* Models a unary reaction where 's1' transforms into 's2'. E.g., A -> B.
     * This fulfills part of requirement 1:
     * "Use operator overloading to support the reaction rule typesetting directly in C++ code." */
    Reaction operator>>=(const Species &speciesL, const Species &speciesR);
    
}

#endif 
