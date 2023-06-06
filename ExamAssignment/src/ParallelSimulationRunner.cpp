#include <queue>
#include "ParallelSimulationRunner.h"
#include "ThreadPool.hpp"

namespace StochSimLib {
    
    void ParallelSimulationRunner::setSimulationCallback(const std::function<void(size_t, const Simulation &)> &simulationCallback) {
        m_simulationCallback = simulationCallback;
    }

    void ParallelSimulationRunner::runSimulationsInParallel(size_t count, 
                                                            double endTime,
                                                            const std::function<Simulation()> &simulationFactory,
                                                            size_t numThreads) {
        m_simulations.resize(count);

        // Helper lambda to run a simulation
        auto runSimulation = [this, endTime, &simulationFactory](size_t index) {
            m_simulations[index] = simulationFactory();
            
            if (m_simulationCallback) {
                m_simulations[index].simulate(endTime, [this, index](const Simulation &simulation) {
                    (*m_simulationCallback)(index, simulation);
                });
            } else {
                m_simulations[index].simulate(endTime);
            }
        };
        
        if (numThreads <= 0) {
            // Run on all available threads
            std::vector threads = std::vector<std::thread>(count);
            
            for (size_t i = 0; i < count; ++i) {
                threads[i] = std::thread(runSimulation, i);
            }
            
            for (std::thread &thread : threads) {
                thread.join();
            }
        } else {
            // Run on specified number of threads
            ThreadPool threadPool{numThreads};
            
            for (size_t i = 0; i < count; ++i) {
                threadPool.addTask([runSimulation, i]() {
                    runSimulation(i);
                });
            }
        }
        
        std::cout << "Done." << std::endl;
        
    }
    
    const std::vector<Simulation> &ParallelSimulationRunner::getSimulations() const {
        return m_simulations;
    }

}