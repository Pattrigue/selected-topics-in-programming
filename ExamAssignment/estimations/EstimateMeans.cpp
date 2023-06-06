#include <vector>
#include "ParallelSimulationRunner.h"
#include "networks/Seihr.cpp"

namespace StochSimLib::Estimations {
    
    /** Fulfills part of requirement 7: 
     * "Use it to estimate the peak of hospitalized agents in Covid-19 example without storing trajectory data". */
    std::pair<size_t, double> estimatePeakAndMean(size_t N = 10000, size_t simulationCount = 100, double endTime = 100.0) {
        std::vector<size_t> peakValues(simulationCount, 0);
        size_t globalPeak = 0;
        std::mutex mtx;

        ParallelSimulationRunner runner;
        runner.setSimulationCallback([&](size_t index, const Simulation &simulation) {
            std::shared_ptr<Species> hospitalized = simulation.species()["H"];
            size_t quantity = hospitalized->quantity();

            std::lock_guard<std::mutex> guard(mtx);
            
            if (quantity > peakValues[index]) {
                peakValues[index] = quantity;
            }
            
            if (quantity > globalPeak) {
                globalPeak = quantity;
            }
        });
        runner.runSimulationsInParallel(simulationCount, endTime, [N]() { return Networks::seihr(N); });

        // Calculate mean peak value
        double mean = 0.0;
        
        for (size_t value: peakValues) {
            mean += static_cast<double>(value);
        }
        
        mean /= static_cast<double>(simulationCount);

        return {mean, globalPeak};
    }
    
}