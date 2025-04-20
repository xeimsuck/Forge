#include "utilite.hpp"
#include <algorithm>

auto Utilite::to_lower(std::string str) -> std::string {
    std::transform(str.begin(), str.end(), str.begin(), [](char ch){
        return std::tolower(ch);
    });
    return str;
}