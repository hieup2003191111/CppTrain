#include <iostream>
#include <vector>
#include "math_library.h"
#include "string_utils.h"

int main() {
    std::cout << "Combined Static and Dynamic Library Example" << std::endl;
    std::cout << "===========================================" << std::endl;

    // Sử dụng static library (math_library)
    std::cout << "\nUsing Static Library (Math Operations):" << std::endl;
    int a = 15, b = 3;
    std::cout << a << " + " << b << " = " << add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << subtract(a, b) << std::endl;
    std::cout << a << " * " << b << " = " << multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << divide(a, b) << std::endl;

    // Sử dụng dynamic library (string_utils)
    std::cout << "\nUsing Dynamic Library (String Operations):" << std::endl;
    std::string original = "Hello, World!";
    std::cout << "Original: " << original << std::endl;
    std::cout << "To Upper: " << stringutils::toUpper(original) << std::endl;
    std::cout << "To Lower: " << stringutils::toLower(original) << std::endl;

    // Sử dụng split và join
    std::string csv = "apple,banana,cherry,date";
    std::cout << "\nSplitting: " << csv << std::endl;
    auto fruits = stringutils::split(csv, ',');
    for (const auto& fruit : fruits) {
        std::cout << "- " << fruit << std::endl;
    }

    std::vector<std::string> words = {"This", "is", "a", "test"};
    std::cout << "\nJoining words: ";
    for (const auto& word : words) {
        std::cout << "\"" << word << "\" ";
    }
    std::cout << std::endl;
    std::cout << "Result: " << stringutils::join(words, " ") << std::endl;

    // Kết hợp cả hai thư viện
    std::cout << "\nCombining Both Libraries:" << std::endl;
    int num1 = 10, num2 = 5;
    int result = add(num1, num2);
    std::string result_str = std::to_string(result);
    std::string message = "The sum of " + std::to_string(num1) + " and " + std::to_string(num2) + " is " + result_str;
    std::cout << stringutils::toUpper(message) << std::endl;

    return 0;
}