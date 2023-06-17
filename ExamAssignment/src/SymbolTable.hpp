#include <optional>
#include <unordered_map>
#include <string>
#include <memory>

namespace StochSimLib {

    /** Symbol table for storing objects of type T. 
     *  This fulfills requirement 3:
     *  "Implement a generic symbol table to store and lookup objects of user-defined types (e.g. information about
     *  agents and reactions). Support failure cases when the table does not contain a looked up value." */
    template<typename T>
    class SymbolTable {
        std::unordered_map<std::string, std::unique_ptr<T>> m_table;

        void checkDuplicate(const std::string &symbol) {
            if (m_table.find(symbol) != m_table.end()) {
                throw std::runtime_error("Symbol \"" + symbol + "\" already exists in symbol table!");
            }
        }

    public:
        T& add(const std::string &symbol, T &&object) {
            checkDuplicate(symbol);
            auto ptr = std::make_unique<T>(std::move(object));
            auto& ref = *ptr;
            m_table[symbol] = std::move(ptr);

            return ref;
        }

        void remove(const std::string &symbol) {
            m_table.erase(symbol);
        }

        std::optional<T*> tryGet(const std::string &symbol) {
            auto it = m_table.find(symbol);

            if (it != m_table.end()) {
                return it->second.get();
            }

            return std::nullopt;
        }

        T& operator[](const std::string &symbol) {
            auto opt = tryGet(symbol);

            if (opt.has_value()) {
                return *opt.value();
            } else {
                throw std::runtime_error("Symbol\"" + symbol + "\"not found in symbol table!");
            }
        }

        [[nodiscard]] size_t size() const {
            return m_table.size();
        }

        auto begin() { return m_table.begin(); }
        auto end() { return m_table.end(); }
        auto begin() const { return m_table.begin(); }
        auto end() const { return m_table.end(); }
    };

}