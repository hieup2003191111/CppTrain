# Getting Started with My C++ Library

Welcome to My C++ Library! This guide will help you get started with using the library, including installation instructions and basic usage examples.

## Installation

To use My C++ Library, you need to have a C++ compiler and CMake installed on your system. Follow these steps to install the library:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/my-cpp-library.git
   cd my-cpp-library
   ```

2. **Create a build directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake to configure the project:**
   ```bash
   cmake ..
   ```

4. **Build the library:**
   ```bash
   make
   ```

5. **Install the library (optional):**
   ```bash
   sudo make install
   ```

## Basic Usage

Here is a simple example of how to use My C++ Library:

1. **Include the library header:**
   ```cpp
   #include "my_library/core.h"
   #include "my_library/version.h"
   ```

2. **Initialize the library:**
   ```cpp
   Core core;
   core.initialize();
   ```

3. **Execute a function:**
   ```cpp
   core.execute();
   ```

4. **Retrieve the version:**
   ```cpp
   std::string version = getVersion();
   std::cout << "Library version: " << version << std::endl;
   ```

5. **Shutdown the library:**
   ```cpp
   core.shutdown();
   ```

## Conclusion

You are now ready to start using My C++ Library! For more detailed information, please refer to the API documentation in `docs/api.md`. If you have any questions or need further assistance, feel free to reach out. Happy coding!