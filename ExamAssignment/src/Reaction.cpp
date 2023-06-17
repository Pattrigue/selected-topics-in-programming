#include "Reaction.h"
#include <random>

namespace StochSimLib {
    
    ReactionCompounds &Reaction::reactants() {
        return m_reactants; 
    }

    ReactionCompounds &Reaction::products() {
        return m_products; 
    }
    
    std::string Reaction::name() const {
        std::stringstream ss;
        ss << m_reactants << " -> " << m_products << " (rate = " << rate << ")";

        return ss.str();
    }

    void Reaction::addReactant(const std::shared_ptr<Species> &reactant) {
        m_reactants.addSpecies(reactant);
    }

    void Reaction::addProduct(const std::shared_ptr<Species> &product) {
        m_products.addSpecies(product);
    }

    void Reaction::computeDelay(std::mt19937 &generator) {
        double lambdaK = rate;

        for (const auto &species : reactants()) {
            lambdaK *= static_cast<double>(species->quantity());
        }

        std::exponential_distribution<double> distribution(lambdaK);
        delay = distribution(generator);
    }
    
    std::ostream &operator<<(std::ostream &os, const Reaction &reaction) {
        return os << reaction.name();
    }

    Reaction operator>>=(ReactionCompounds &&compounds, const std::shared_ptr<Species> &species) {
        Reaction reaction;

        for (const auto &s: compounds.species()) {
            reaction.addReactant(s);
        }

        reaction.addProduct(species);

        return reaction;
    }

    Reaction operator>>=(const std::shared_ptr<Species> &species, ReactionCompounds &&compounds) {
        Reaction reaction;
        reaction.addReactant(species);

        for (const auto &s: compounds.species()) {
            reaction.addProduct(s);
        }

        return reaction;
    }

    Reaction operator>>=(const ReactionCompounds &compoundsL, const ReactionCompounds &compoundsR) {
        Reaction reaction;

        for (const auto &s: compoundsL.species()) {
            reaction.addReactant(s);
        }

        for (const auto &s: compoundsR.species()) {
            reaction.addProduct(s);
        }

        return reaction;
    }

    Reaction operator>>=(const std::shared_ptr<Species> &speciesL, const std::shared_ptr<Species> &speciesR) {
        Reaction reaction;
        reaction.addReactant(speciesL);
        reaction.addProduct(speciesR);

        return reaction;
    }
    
}