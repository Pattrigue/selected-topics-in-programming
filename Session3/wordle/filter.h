//
// Created by Patrick on 11/02/2023.
//

#ifndef WORDLE_FILTER_H
#define WORDLE_FILTER_H

#include <vector>
#include <string>

namespace wordle {
    std::vector<std::string> filter(std::vector<std::string> &&words, const std::string &pattern);
}

#endif 
