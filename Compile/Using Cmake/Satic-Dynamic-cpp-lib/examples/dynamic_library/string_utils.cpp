// string_utils.cpp
#include "string_utils.h"
#include <algorithm>
#include <sstream>

namespace stringutils {

std::string toUpper(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string toLower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string join(const std::vector<std::string>& strings, const std::string& delimiter) {
    std::string result;
    
    for (size_t i = 0; i < strings.size(); ++i) {
        if (i > 0) {
            result += delimiter;
        }
        result += strings[i];
    }
    
    return result;
}

} // namespace stringutils
