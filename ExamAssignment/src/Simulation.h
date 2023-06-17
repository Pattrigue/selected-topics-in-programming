#ifndef STOCHSIMLIB_SIMULATION_H
#define STOCHSIMLIB_SIMULATION_H

#include <iostream>
#include <fstream>
#include <random>
#include <functional>
#include "Species.h"
#include "SymbolTable.hpp"
#include "Reaction.h"

namespace StochSimLib {
    
    class Simulation {
        std::unique_ptr<Species> env = std::make_unique<Species>("env", 0);
        std::unique_ptr<SymbolTable<Species>> m_species = std::make_unique<SymbolTable<Species>>();
        std::unique_ptr<SymbolTable<Reaction>> m_reactions = std::make_unique<SymbolTable<Reaction>>();
        
        double m_time;

        /** Returns true if the reaction can proceed (all reactants have a sufficient quantity). */
        static bool canReact(Reaction& reaction);

        /** Performs the reaction by decreasing the quantity of reactants and increasing the quantity of products. */
        static void react(Reaction& reaction);
        
        /** Returns the reaction with the minimum delay. */
        Reaction& getReactionWithMinDelay();

    public:
        [[nodiscard]] Species& environment() const;

        [[nodiscard]] SymbolTable<Species>& species() const;

        [[nodiscard]] SymbolTable<Reaction>& reactions() const;

        /** The current time of the simulation. */
        [[nodiscard]] double time() const;
        
        /** Creates a new species and adds it to the simulation. */
        Species& addSpecies(const std::string &name, size_t quantity);

        /** Creates a new reaction and adds it to the simulation. */
        void addReaction(Reaction &&reaction, double rate);

        /** Simulates the reactions until the given end time, invoking the callback function after each iteration with
         * the current simulation state. 
         * This fulfills part of requirement 4: 
         * "Implement the stochastic simulation of the system using the reaction rules." 
         * The callback function is used to fulfill part of requirement 7:
         * "Implement a generic support for the state monitor in the stochastic simulation algorithm." */
        void simulate(double endTime, std::optional<std::function<void(const Simulation&)>> callback = std::nullopt);

        /** Pretty-prints the reactions in the simulation. This fulfills part of requirement 2:
         * "Pretty-print the reaction network in a human readable format". */
        friend std::ostream &operator<<(std::ostream &os, const Simulation &simulation);
    };
    
}

#endif 
