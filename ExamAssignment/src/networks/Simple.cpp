#ifndef STOCHSIMLIB_SIMPLE_CPP
#define STOCHSIMLIB_SIMPLE_CPP

#include "Simulation.h"
#include "Reaction.h"

namespace StochSimLib::Networks {
    
    /** Creates a simulation of a simple reaction network based on the model from the PDF. */
    Simulation simple(size_t countA = 100, size_t countB = 0, size_t countC = 1) {
        const double lambda = 0.001;

        Simulation simulation{};

        auto A = simulation.addSpecies("A", countA);
        auto B = simulation.addSpecies("B", countB);
        auto C = simulation.addSpecies("C", countC);

        simulation.addReaction(A + C >>= B + C, lambda);

        return simulation;
    }

}

#endif