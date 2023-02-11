#include <locale>
#include "token.h"

namespace wordle {
    token::token(char prefix, char character)
            : m_prefix(prefix), m_char(std::tolower(character, std::locale()))
    {
    }

    token::token(char character)
            : token('\0', character)
    {
    }

    bool token::has_prefix() const {
        return m_prefix != '\0';
    }

    char token::prefix() const {
        return m_prefix;
    }

    char token::character() const {
        return m_char;
    }

    bool token::is_token(char c) {
        return c == TOKEN_PRESENT || c == TOKEN_ABSENT;
    }
} 