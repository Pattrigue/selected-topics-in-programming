#include "Simulation.h"

namespace StochSimLib {

    bool Simulation::canReact(Reaction &reaction) {
        return std::all_of(
                reaction.reactants().begin(),
                reaction.reactants().end(),
                [](const auto &reactant) {
                    return reactant->quantity() > 0;
                }
        );
    }
    
    void Simulation::react(Reaction &reaction) {
        for (auto &reactant : reaction.reactants()) {
            reactant->decreaseQuantity(1);
        }

        for (auto &product : reaction.products()) {
            product->increaseQuantity(1);
        }
    }
    
    Reaction &Simulation::getReactionWithMinDelay() {
        auto reactionMinDelayIter = std::min_element(m_reactions.begin(), m_reactions.end(),
              [](const auto &a, const auto &b) {
                return a.second->delay < b.second->delay;
            }
        );

        return *reactionMinDelayIter->second;
    }
    
    std::shared_ptr<Species> Simulation::environment() const {
        return env;
    }
    
    SymbolTable<Species> Simulation::species() const {
        return m_species;
    }

    SymbolTable<Reaction> Simulation::reactions() const {
        return m_reactions;
    }
    
    double Simulation::time() const {
        return m_time;
    }
    
    std::shared_ptr<Species> Simulation::addSpecies(const std::string &name, size_t quantity) {
        std::shared_ptr<Species> species = std::make_shared<Species>(name, quantity);

        m_species.add(species->name(), species);

        return species;
    }

    void Simulation::addReaction(Reaction &&reaction, double rate) {
        reaction.rate = rate;
        m_reactions.add(reaction.name(), std::make_shared<Reaction>(reaction));
    }
    
    void Simulation::simulate(double endTime, std::optional<std::function<void(const Simulation &)>> callback) {
        std::random_device rd;
        std::mt19937 generator(rd());

        while (m_time <= endTime) {
            for (auto &[_, reaction] : m_reactions) {
                reaction->computeDelay(generator);
            }

            Reaction& reactionMinDelay = getReactionWithMinDelay();
            m_time += reactionMinDelay.delay;

            if (canReact(reactionMinDelay)) {
                react(reactionMinDelay);
            }

            if (callback) {
                (*callback)(*this);
            }
        }
    }

    std::ostream &operator<<(std::ostream &os, const Simulation &simulation) {
        for (const auto &[_, reaction]: simulation.m_reactions) {
            os << reaction;
            os << " (rate = " << reaction->rate << ")";
            os << std::endl;
        }

        return os;
    }

}