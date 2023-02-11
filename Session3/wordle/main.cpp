#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <random>

#include "filter.h"
#include "js_parser.h"
#include "token.h"

bool is_input_valid(const std::string &input);
std::string select_random_word(const std::vector<std::string> &words);


int main() {
    std::ifstream file("wordle.js");

    const auto database = wordle::parse_js_file(std::move(file));

    auto words = database; // make a copy of the database
    auto guess = std::string{}; // allocate memory to store guess patterns

    while (words.size() > 1) {
        std::cout << words.size() << " words remaining" << std::endl;
        bool good;

        do {
            std::cout << "Enter a guess pattern:" << std::endl;
            std::cin >> guess;

            good = is_input_valid(guess);
        } while (!good);

        /* apply the filter on the words */
        words = wordle::filter(std::move(words), guess);
        
        /* pick and announce one of the words for the user to try */
        auto selected_word = select_random_word(words);
        std::cout << "Try this word: " << selected_word << std::endl;
    }

    if (words.size() == 1) {
        std::cout << "Congratulations: " << words.front() << std::endl;
    } else {
        std::cerr << "Something got messed up :-(\n";
    }
}

bool is_input_valid(const std::string &input)  {
    static const std::regex pattern(
            std::string("^[") + wordle::TOKEN_PRESENT + "-]?[A-Za-z][" + wordle::TOKEN_PRESENT + "-]?[A-Za-z][" +
            wordle::TOKEN_PRESENT + "-]?[A-Za-z][" + wordle::TOKEN_PRESENT + "-]?[A-Za-z][" +
            wordle::TOKEN_PRESENT + "-]?[A-Za-z]$");
    return std::regex_match(input, pattern);
}

std::string select_random_word(const std::vector<std::string> &words) {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution dist(0, static_cast<int>(words.size()) - 1);

    auto selected_word = words[dist(engine)];

    return selected_word;
}
