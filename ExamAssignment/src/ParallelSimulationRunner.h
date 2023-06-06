#ifndef STOCHSIMLIB_PARALLELSIMULATIONRUNNER_H
#define STOCHSIMLIB_PARALLELSIMULATIONRUNNER_H

#include <thread>
#include <functional>
#include "Simulation.h"

namespace StochSimLib {

    class ParallelSimulationRunner {
        std::vector<Simulation> m_simulations;
        
        /** Callback invoked after each simulation iteration with the index of the simulation and the simulation state. */
        std::optional<std::function<void(size_t, const Simulation&)>> m_simulationCallback;
        
    public:
        /** Sets the callback invoked after each simulation iteration with the index of the simulation and the simulation state. */
        void setSimulationCallback(const std::function<void(size_t, const Simulation&)> &simulationCallback);
        
        /** Runs the given number of simulations in parallel on the given number of threads where each simulation runs 
         * until the given end time. The given simulation factory is used to create each simulation.
         * This fulfills part of requirement 8: "Implement support for multiple computer cores by parallelizing the 
         * computation of several simulations at the same time. */
        void runSimulationsInParallel(size_t count, double endTime, const std::function<Simulation()> &simulationFactory, size_t numThreads = 0);

        /** Returns the simulations. */
        [[nodiscard]] const std::vector<Simulation>& getSimulations() const;
    };

}

#endif
