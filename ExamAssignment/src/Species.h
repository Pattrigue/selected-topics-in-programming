#ifndef STOCHSIMLIB_SPECIES_H
#define STOCHSIMLIB_SPECIES_H

#include <string>

namespace StochSimLib {

    class Species {
        std::string m_name;
        size_t m_quantity;

    public:
        Species(std::string name, size_t quantity);

        [[nodiscard]] std::string name() const;

        [[nodiscard]] size_t quantity() const;
        
        void increaseQuantity(size_t amount);
        
        void decreaseQuantity(size_t amount);
    };

}

#endif
