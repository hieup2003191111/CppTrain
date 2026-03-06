#include <iostream>
#include "my_library/core.h"

int main() {
    // Example usage of the library
    MyLibrary::Core core;
    core.initialize();

    std::cout << "Library version: " << MyLibrary::getVersion() << std::endl;

    core.performTask();

    return 0;
}