#ifndef WORDLE_JS_PARSER_H
#define WORDLE_JS_PARSER_H

#include <vector>
#include <string>

namespace wordle {
    std::vector<std::string> parse_js_file(std::istream &&is);
}

#endif 
