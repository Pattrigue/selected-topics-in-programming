#include "networks/Simple.cpp"
#include "networks/CircadianOscillator.cpp"
#include "networks/Seihr.cpp"
#include "SimulationFileWriter.h"
#include "graphs/ReactionNetworkDrawer.h"

using namespace StochSimLib;
using namespace StochSimLib::Graphs;

/** Demonstrates the application of the library on the three examples from the PDF. Fulfills requirement 5. */
int main() {
    auto example1 = Networks::simple();
    auto example2 = Networks::circadianOscillator();
    auto example3 = Networks::seihr();

    SimulationFileWriter fileWriter1{example1, "simple.csv"};
    SimulationFileWriter fileWriter2{example2, "circadianOscillator.csv"};
    SimulationFileWriter fileWriter3{example3, "seihr.csv"};

    ReactionNetworkDrawer::draw(example1, "simple", "png");
    ReactionNetworkDrawer::draw(example2, "circadianOscillator", "png");
    ReactionNetworkDrawer::draw(example3, "seihr", "png");

    example1.simulate(2000, [&fileWriter1](const Simulation &simulation) {
        fileWriter1.logState(simulation);
    });

    example2.simulate(72, [&fileWriter2](const Simulation &simulation) {
        fileWriter2.logState(simulation);
    });

    example3.simulate(100, [&fileWriter3](const Simulation &simulation) {
        fileWriter3.logState(simulation);
    });
    
    return 0;
}