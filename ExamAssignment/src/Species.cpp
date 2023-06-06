#include <stdexcept>
#include "Species.h"

namespace StochSimLib {

    Species::Species(std::string name, size_t quantity) : m_name(std::move(name)), m_quantity(quantity) {}

    std::string Species::name() const {
        return m_name;
    }

    size_t Species::quantity() const {
        return m_quantity;
    }

    void Species::increaseQuantity(size_t amount) {
        m_quantity += amount;
    }

    void Species::decreaseQuantity(size_t amount) {
        if (amount > m_quantity) {
            throw std::runtime_error("Cannot decrease quantity of " + m_name + " by " + std::to_string(amount) + " as it only has " + std::to_string(m_quantity) + " left.");
        }
        
        m_quantity -= amount;
    }

}