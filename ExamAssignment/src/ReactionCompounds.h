#ifndef STOCHSIMLIB_REACTIONCOMPOUNDS_H
#define STOCHSIMLIB_REACTIONCOMPOUNDS_H

#include <iostream>
#include <vector>
#include <memory>
#include "Species.h"

namespace StochSimLib {
    
    class ReactionCompounds {
        std::vector<std::shared_ptr<Species>> m_species;

    public:
        [[nodiscard]] const std::vector<std::shared_ptr<Species>> &species() const;

        void addSpecies(const std::shared_ptr<Species> &species);

        [[nodiscard]] std::vector<std::shared_ptr<Species>>::const_iterator begin() const;

        [[nodiscard]] std::vector<std::shared_ptr<Species>>::const_iterator end() const;

        std::vector<std::shared_ptr<Species>>::iterator begin();

        std::vector<std::shared_ptr<Species>>::iterator end();

        /** Operator overload for pretty-printing a ReactionCompounds object to an output stream. 
         * Fulfills part of requirement 2: "Pretty-print the reaction network in human readable format". */
        friend std::ostream &operator<<(std::ostream &os, const ReactionCompounds &compounds);
    };

    /** Operator overload for creating a reaction rule between two species (resulting in a ReactionCompounds object).
     * "Use operator overloading to support the reaction rule typesetting directly in C++ code." */
    ReactionCompounds operator+(const std::shared_ptr<Species> &speciesL, const std::shared_ptr<Species> &speciesR);

    /** Operator overload for creating a reaction rule between a ReactionCompounds object and a species
     * (adding the species to the ReactionCompounds object). Fulfills part of requirement 1:
     * "Use operator overloading to support the reaction rule typesetting directly in C++ code." */
    ReactionCompounds operator+(ReactionCompounds &&compounds, const std::shared_ptr<Species> &species);
}

#endif 
