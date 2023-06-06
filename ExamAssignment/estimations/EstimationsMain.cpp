#include "EstimateMeans.cpp"
#include <iostream>

using namespace StochSimLib::Estimations;

int main() {
    size_t N_DK = 5822763;
    size_t N_NJ = 589755;
    size_t simulationCount = 100;

    auto result_DK = estimatePeakAndMean(N_DK, simulationCount);
    auto result_NJ = estimatePeakAndMean(N_NJ, simulationCount);

    std::cout << "Mean DK hospitalized: " << result_DK.first << std::endl;
    std::cout << "Mean NJ hospitalized: " << result_NJ.first << std::endl;
    std::cout << "Peak DK hospitalized: " << result_DK.second << std::endl;
    std::cout << "Peak NJ hospitalized: " << result_NJ.second << std::endl;

    return 0;
}
