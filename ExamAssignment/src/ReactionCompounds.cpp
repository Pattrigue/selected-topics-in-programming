#include "ReactionCompounds.h"

namespace StochSimLib {

    const std::vector<std::shared_ptr<Species>> &ReactionCompounds::species() const {
        return m_species;
    }

    void ReactionCompounds::addSpecies(const std::shared_ptr<Species> &species) {
        m_species.emplace_back(species);
    }

    std::vector<std::shared_ptr<Species>>::const_iterator ReactionCompounds::begin() const { return m_species.begin(); }

    std::vector<std::shared_ptr<Species>>::const_iterator ReactionCompounds::end() const { return m_species.end(); }

    std::vector<std::shared_ptr<Species>>::iterator ReactionCompounds::begin() { return m_species.begin(); }

    std::vector<std::shared_ptr<Species>>::iterator ReactionCompounds::end() { return m_species.end(); }
    
    std::ostream &operator<<(std::ostream &os, const ReactionCompounds &compounds) {
        for (size_t i = 0; i < compounds.m_species.size(); ++i) {
            os << compounds.m_species[i]->name();

            if (i < compounds.m_species.size() - 1) {
                os << " + ";
            }
        }

        return os;
    }
    
    ReactionCompounds operator+(const std::shared_ptr<Species> &speciesL, const std::shared_ptr<Species> &speciesR) {
        ReactionCompounds compounds;

        compounds.addSpecies(speciesL);
        compounds.addSpecies(speciesR);

        return compounds;
    }

    ReactionCompounds operator+(ReactionCompounds &&compounds, const std::shared_ptr<Species> &species) {
        compounds.addSpecies(species);

        return compounds;
    }

}