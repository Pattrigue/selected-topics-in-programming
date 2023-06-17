#include "ReactionCompounds.h"

namespace StochSimLib {

    const std::vector<std::reference_wrapper<const Species>> &ReactionCompounds::species() const {
        return m_species;
    }

    void ReactionCompounds::addSpecies(const Species& species) {
        m_species.emplace_back(species);
    }

    std::vector<std::reference_wrapper<const Species>>::const_iterator ReactionCompounds::begin() const { return m_species.begin(); }

    std::vector<std::reference_wrapper<const Species>>::const_iterator ReactionCompounds::end() const { return m_species.end(); }

    std::vector<std::reference_wrapper<const Species>>::iterator ReactionCompounds::begin() { return m_species.begin(); }
    
    std::vector<std::reference_wrapper<const Species>>::iterator ReactionCompounds::end() { return m_species.end(); }
    
    std::ostream &operator<<(std::ostream &os, const ReactionCompounds &compounds) {
        for (size_t i = 0; i < compounds.m_species.size(); ++i) {
            os << compounds.m_species[i].get().name();

            if (i < compounds.m_species.size() - 1) {
                os << " + ";
            }
        }

        return os;
    }
    
    ReactionCompounds operator+(const Species& speciesL, const Species& speciesR) {
        ReactionCompounds compounds;

        compounds.addSpecies(speciesL);
        compounds.addSpecies(speciesR);

        return compounds;
    }

    ReactionCompounds operator+(ReactionCompounds &&compounds, const Species &species) {
        compounds.addSpecies(species);

        return compounds;
    }

}