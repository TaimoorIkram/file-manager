#include "utils.hpp"

namespace fs {
    std::vector<std::string> FSUtils::splitString(std::string& str, std::string delimiter) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        size_t delimiterLength = delimiter.length();

        while ((pos = str.find(delimiter)) != std::string::npos) {
            tokens.push_back(str.substr(0, pos));
            str.erase(0, pos + delimiterLength);
        }
        tokens.push_back(str); // Push the remaining part of the string after the last delimiter
        return tokens;
    }
}