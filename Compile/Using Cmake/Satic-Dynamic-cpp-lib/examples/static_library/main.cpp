// main.cpp
#include <iostream>
#include "math_library.h"

int main() {
    std::cout << "Static Library Example\n";
    std::cout << "----------------------\n";
    
    int a = 10;
    int b = 5;
    
    std::cout << a << " + " << b << " = " << add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << subtract(a, b) << std::endl;
    std::cout << a << " * " << b << " = " << multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << divide(a, b) << std::endl;
    
    return 0;
}
