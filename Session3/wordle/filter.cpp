#include <string>
#include <vector>
#include "token.h"
#include "search_word.h"

namespace wordle {
    static bool same_spot(const token &token, std::string word) {
        return word[token.position()] == token.character();
    }

    std::vector<std::string> filter(std::vector<std::string> &&words, const std::string &pattern) {
        search_word search_word{pattern};
        std::string search_word_str = search_word.string();

        for (const auto &token: search_word.tokens()) {
            if (token.has_prefix()) {
                if (token.prefix() == TOKEN_ABSENT) {
                    // token is not in this spot
                    std::erase_if(words, [&token](const std::string &word) {
                        return same_spot(token, word);
                    });
                }
            } else {
                // token is in the right spot already
                std::erase_if(words, [&token](const std::string &word) {
                    return !same_spot(token, word);
                });
            }
        }

        return words;
    }
}
