#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

constexpr char TOKEN_PRESENT = '+';
constexpr char TOKEN_ABSENT = '-';

class token {
public:
    token(char prefix, char character)
            : m_prefix(prefix), m_char(std::tolower(character, std::locale())) 
    {
    }
    
    explicit token(char character)
            : token('\0', character)
    {
    }
    
    bool has_prefix() const {
        return m_prefix != '\0';
    }
    
    char prefix() const {
        return m_prefix;
    }
    
    char character() const {
        return m_char;
    }
    
    static bool is_token(char c) {
        return c == TOKEN_PRESENT || c == TOKEN_ABSENT; 
    }
private:
    char m_prefix;
    char m_char;
};


std::vector<std::string> read_wordle_js(std::istream&& is)
{
    std::vector<std::string> words;
    auto word = std::string{};
    while (is) { // check for EOF and potential I/O errors
        if (is.peek() == '"') { // look for an opening quote
            is >> std::quoted(word); // read the word in quotes and remove quotes
            if (word.length() == 5 && // must be 5-letter word
                std::ranges::all_of(std::cbegin(word), std::cend(word), // all lower-case letters
                            [](char c) { return std::isalpha(c) && std::islower(c); }))
                words.push_back(word);
        } else
            is.get(); // skip one m_char
    }
    
    std::ranges::sort(std::begin(words), std::end(words));
    words.erase(std::unique(std::begin(words), std::end(words)), words.end());
    return words;
}

std::vector<token> get_tokens(const std::string& pattern) {
    std::vector<token> tokens;

    for (std::size_t i = 0; i < pattern.size(); ++i) {
        char c = pattern[i];
        
        if (!token::is_token(c) && i > 0) {
            char prev = pattern[i - 1];
            
            if (token::is_token(prev)) {
                tokens.emplace_back( prev, c );
            } else {
                tokens.emplace_back( c );
            }
        }
    }
    
    return tokens;
}

std::vector<std::string> filter(std::vector<std::string>&& words, const std::string& pattern)
{
    auto tokens = get_tokens(pattern);

    std::cout << words.size() << std::endl;
    
    for (const auto &token: tokens) {
        if (token.has_prefix()) {
            if (token.prefix() == TOKEN_ABSENT) {
                auto pred = [&token](const std::string& word) {
                    return word.find(token.character()) != std::string::npos;
                };

                erase_if(words, pred);
            }
        }
    }
    
    std::cout << words.size() << std::endl;
    
    return words;
}

int main()
{
    std::ifstream file("wordle.js");
    
    /* read the database from the javascript file */
    const auto database = read_wordle_js(std::move(file));

    auto words = database; // make a copy of the database
    auto guess = std::string{}; // allocate memory to store guess patterns

    filter(std::move(words), "+S-L-I-DE");
    
    return 1;
    while (words.size()>1) {
        std::cout << words.size() << " words remaining\n";
        bool good = true;
        do {
            std::cout << "Enter a guess pattern: ";
            std::cin >> guess;
            /* sanitize: set good to false if input fails to follow the pattern */
        } while (!good);
        
        /* apply the filter on the words */
        auto filtered_words = filter(std::move(words), guess);
        
        /* pick and announce one of the words for the user to try */
    }

    if (words.size() == 1) {
        std::cout << "Congratulations: " << words.front() << "\n";
    } else {
        std::cerr << "Something got messed up :-(\n";
    }
}