#include <benchmark/benchmark.h>
#include "ParallelSimulationRunner.h"
#include "networks/CircadianOscillator.cpp"

/** Benchmarks fulfilling requirement 10: 
 * "Benchmark and compare the stochastic simulation performance (e.g. the time it takes to compute 20 simulations
 * a single core, multiple cores, or improved implementation)". */

constexpr double endTime = 24;
constexpr size_t simulationCount = 128;
constexpr size_t numIterations = 100;

StochSimLib::Simulation simulationFactory() {
    return StochSimLib::Networks::circadianOscillator();
}

// Benchmark for varying number of simulations with a single thread
static void BM_Simulations_Synchronous(benchmark::State& state) {
    size_t numSimulations = state.range(0);
    
    std::vector<StochSimLib::Simulation> simulations(numSimulations);
    
    for (auto _ : state) {
        for (auto& simulation : simulations) {
            simulation = simulationFactory();
            simulation.simulate(endTime);
        }
    }
}

BENCHMARK(BM_Simulations_Synchronous)->Iterations(numIterations)->RangeMultiplier(2)->Range(1, simulationCount);

// Benchmark for varying number of threads and simulations together
static void BM_SimulationsAndThreads(benchmark::State& state) {
    StochSimLib::ParallelSimulationRunner runner;
    size_t numSimulations = state.range(0);
    size_t numThreads = state.range(1);

    for (auto _ : state) {
        runner.runSimulationsInParallel(numSimulations, endTime, simulationFactory, numThreads);
    }
}

// Custom Arguments for the above benchmark
static void customThreadAndSimulationCountArguments(benchmark::internal::Benchmark* b) {
    std::vector<int> threadCounts;

    for (int i = 2; i <= std::thread::hardware_concurrency(); i *= 2) {
        threadCounts.push_back(i);
    }
    
    // Add the case with 0 threads for the simulation runner (becomes OS choice)
    for (int simulations = 1; simulations <= simulationCount; simulations *= 2) {
        b->Args({simulations, 0}); 
    }

    for (const auto& threads : threadCounts) {
        for (int simulations = 1; simulations <= simulationCount; simulations *= 2) {
            b->Args({simulations, threads});
        }
    }
}

BENCHMARK(BM_SimulationsAndThreads)->Iterations(numIterations)->Apply(customThreadAndSimulationCountArguments);


int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}