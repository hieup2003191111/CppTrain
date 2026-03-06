// main.cpp
#include <iostream>
#include <vector>
#include "string_utils.h"

int main() {
    std::cout << "Dynamic Library Example\n";
    std::cout << "----------------------\n";
    
    // Test toUpper
    std::string text = "Hello, World!";
    std::cout << "Original: " << text << std::endl;
    std::cout << "To Upper: " << stringutils::toUpper(text) << std::endl;
    
    // Test toLower
    std::cout << "To Lower: " << stringutils::toLower(text) << std::endl;
    
    // Test split
    std::string csv = "apple,banana,cherry,date";
    std::cout << "\nSplitting: " << csv << std::endl;
    std::vector<std::string> fruits = stringutils::split(csv, ',');
    for (const auto& fruit : fruits) {
        std::cout << "- " << fruit << std::endl;
    }
    
    // Test join
    std::vector<std::string> words = {"This", "is", "a", "test"};
    std::cout << "\nJoining words: ";
    for (const auto& word : words) {
        std::cout << "\"" << word << "\" ";
    }
    std::cout << std::endl;
    std::cout << "Result: " << stringutils::join(words, " ") << std::endl;
    
    return 0;
}
