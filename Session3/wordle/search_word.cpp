#include "search_word.h"

namespace wordle {
    search_word::search_word(const std::string &pattern)
            : m_string(search_pattern_to_string(pattern))
    {
        for (std::size_t i = 0; i < pattern.size(); i++) {
            char c = pattern[i];
            
            if (token::is_presence_token(c)) {
                continue;
            }

            if (i == 0) {
                add_token(c);
                continue;
            }

            char prev = pattern[i - 1];

            if (!token::is_presence_token(prev)) {
                add_token(c);
            } else {
                add_token(prev, c);
            }
        }
    }

    std::string search_word::string() const {
        return m_string;
    }
    
    token search_word::operator[](int index) const {
        return m_tokens[index];
    }
    
    const std::vector<token> &search_word::tokens() const {
        return m_tokens;
    }
    
    void search_word::add_token(char prefix, char character) {
        add_token(token { prefix, character, static_cast<int>(m_tokens.size()) });
    }

    void search_word::add_token(char character) {
        add_token(token { character, static_cast<int>(m_tokens.size()) });
    }
    
    void search_word::add_token(const token &token) {
        m_tokens.push_back(token);
    }
    
    std::string search_word::search_pattern_to_string(const std::string& pattern) {
        std::string s;

        // create a new string without the tokens from the pattern
        for (char c : pattern) {
            if (c != TOKEN_PRESENT && c != TOKEN_ABSENT) {
                s += c;
            }
        }
        
        // convert it to lowercase
        std::transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c) { return std::tolower(c); });

        return s;
    }
} 