#include <iostream>
#include "my_library/core.h"
#include "my_library/version.h"

int main() {
    // Create an instance of the Core class
    my_library::Core core;

    // Initialize the library
    core.initialize();

    // Execute a function
    core.execute();

    // Retrieve and print the version
    std::cout << "Library version: " << my_library::getVersion() << std::endl;

    // Shutdown the library
    core.shutdown();

    return 0;
}