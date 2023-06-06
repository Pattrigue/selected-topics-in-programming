#include "SimulationFileWriter.h"

namespace StochSimLib {
    
    SimulationFileWriter::SimulationFileWriter(const Simulation &simulation, const std::string &fileName) {
        m_outputFile = std::make_unique<std::ofstream>(fileName);

        for (const auto &species : simulation.species()) {
            *m_outputFile << species.second->name() << ",";
        }

        *m_outputFile << "Time\n";
    }

    SimulationFileWriter::~SimulationFileWriter() {
        m_outputFile->close();
    }
    
    void SimulationFileWriter::logState(const Simulation &simulation) {
        for (const auto &species : simulation.species()) {
            *m_outputFile << species.second->quantity() << ",";
        }
        
        *m_outputFile << simulation.time() << "\n";
    }

}
