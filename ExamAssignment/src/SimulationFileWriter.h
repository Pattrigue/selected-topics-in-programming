#ifndef STOCHSIMLIB_SIMULATIONFILEWRITER_H
#define STOCHSIMLIB_SIMULATIONFILEWRITER_H

#include <memory>
#include "Simulation.h"

namespace StochSimLib {

    class SimulationFileWriter {
        std::unique_ptr<std::ofstream> m_outputFile;
        
    public:
        SimulationFileWriter(const Simulation& simulation, const std::string& fileName);
        
        ~SimulationFileWriter();
        
        void logState(const Simulation& simulation);
    
    };
}

#endif
