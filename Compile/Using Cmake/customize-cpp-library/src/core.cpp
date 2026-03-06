#include "my_library/core.h"
#include <iostream>

namespace my_library {

void Core::initialize() {
    std::cout << "Library initialized." << std::endl;
}

void Core::execute() {
    std::cout << "Executing core functionality." << std::endl;
}

void Core::shutdown() {
    std::cout << "Library shutdown." << std::endl;
}

} // namespace my_library