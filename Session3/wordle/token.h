#ifndef WORDLE_TOKEN_H
#define WORDLE_TOKEN_H

namespace wordle {
    constexpr char TOKEN_PRESENT = '+';
    constexpr char TOKEN_ABSENT = '-';
    
    class token {
    public:
        token(char prefix, char character);
        explicit token(char character);

        bool has_prefix() const;
        char prefix() const;
        char character() const;
        static bool is_token(char c);
    private:
        char m_prefix;
        char m_char;
    };
}

#endif //WORDLE_TOKEN_H
