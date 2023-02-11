#include <locale>
#include "token.h"

namespace wordle {
    token::token(char prefix, char character, int position)
            : m_prefix(prefix), m_char(std::tolower(character, std::locale())), m_position(position)
    {
    }

    token::token(char character, int position)
            : token('\0', character, position)
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
    
    int token::position() const {
        return m_position;
    }

    bool token::is_presence_token(char c) {
        return c == TOKEN_PRESENT || c == TOKEN_ABSENT;
    }
} 