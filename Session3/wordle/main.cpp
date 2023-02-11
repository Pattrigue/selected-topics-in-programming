#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "search_word.h"

namespace wordle {
    std::vector<std::string> read_wordle_js(std::istream &&is) {
        std::vector<std::string> words;
        auto word = std::string{};
        
        while (is) { // check for EOF and potential I/O errors
            if (is.peek() == '"') { // look for an opening quote
                is >> std::quoted(word); // read the m_string in quotes and remove quotes
                if (word.length() == 5 && // must be 5-letter m_string
                    std::ranges::all_of(std::cbegin(word), std::cend(word), // all lower-case letters
                                        [](char c) { return std::isalpha(c) && std::islower(c); }))
                    words.push_back(word);
            } else {
                is.get(); // skip one m_char
            }
        }

        std::ranges::sort(std::begin(words), std::end(words));
        words.erase(std::unique(std::begin(words), std::end(words)), words.end());
        
        return words;
    }

    bool same_spot(const token &token, std::string word) {
        return word[token.position()] == token.character();
    }

    std::vector<std::string> filter(std::vector<std::string> &&words, const std::string &pattern) {
        search_word search_word { pattern };
        std::string search_word_str = search_word.string();

        for (const auto &token: search_word.tokens()) {
            std::cout << token.prefix() << token.character() << std::endl;
            if (token.has_prefix()) {
                if (token.prefix() == TOKEN_ABSENT) {
                    // token is not in this spot
                    std::erase_if(words, [&token](const std::string &word) {
                        return same_spot(token, word);
                    });
                } else if (token.prefix() == TOKEN_PRESENT) {
                    // token is present but in a different spot
                }
            } else {
                // token is in the right spot already
                std::erase_if(words, [&token](const std::string &word) { 
                    return !same_spot(token, word); 
                });
            }
        }

        std::cout << words.size() << std::endl;
//        for (const auto &item: words) {
//            std::cout << item << std::endl;
//        }
//
        return words;
    }
}

int main() {
    std::ifstream file("wordle.js");

    /* read the database from the javascript file */
    const auto database = wordle::read_wordle_js(std::move(file));

    auto words = database; // make a copy of the database
    auto guess = std::string{}; // allocate memory to store guess patterns
    
    // wordle::filter(std::move(words), "+S-L-I-DE");

    while (words.size() > 1) {
        std::cout << words.size() << " words remaining" << std::endl;
        bool good = true;
        
        // guess = "+S-L-I-DE";
        do {
            std::cout << "Enter a guess pattern:" << std::endl;
            std::cin >> guess;
            /* TODO: sanitize - set good to false if input fails to follow the pattern */
        } while (!good);

        /* apply the filter on the words */
        words = wordle::filter(std::move(words), guess);

        /* pick and announce one of the words for the user to try */
        auto selected_word = words[rand() % words.size()];
        std::cout << "Try this word: " << selected_word << std::endl;
    }

    if (words.size() == 1) {
        std::cout << "Congratulations: " << words.front() << "\n";
    } else {
        std::cerr << "Something got messed up :-(\n";
    }
}
