#ifndef WORDLE_SEARCH_WORD_H
#define WORDLE_SEARCH_WORD_H

#include <string>
#include <vector>
#include "token.h"

namespace wordle {
    class search_word {
    public:
        explicit search_word(const std::string& pattern);
        [[nodiscard]] std::string string() const;
        token operator[](int index) const;
        [[nodiscard]] const std::vector<token> &tokens() const;
    private:
        std::vector<token> m_tokens;
        std::string m_string;

        void add_token(char prefix, char character);
        void add_token(char character);
        void add_token(const token &token);
        static std::string search_pattern_to_string(const std::string& pattern);
    };
} 

#endif //WORDLE_SEARCH_WORD_H
