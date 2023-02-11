#ifndef WORDLE_TOKEN_H
#define WORDLE_TOKEN_H

namespace wordle {
    constexpr char TOKEN_PRESENT = '+';
    constexpr char TOKEN_ABSENT = '-';
    
    class token {
    public:
        token(char prefix, char character, int position);
        explicit token(char character, int position);

        bool has_prefix() const;
        char prefix() const;
        char character() const;
        int position() const;
        static bool is_presence_token(char c);
    private:
        char m_prefix;
        char m_char;
        int m_position;
    };
}

#endif //WORDLE_TOKEN_H
