# API Documentation for My C++ Library

## Overview

This document provides an overview of the API for the My C++ Library. It includes details about the classes, methods, and their usage.

## Classes

### Core

The `Core` class provides the main functionalities of the library.

#### Methods

- **`void initialize()`**
  - Initializes the library. This method must be called before any other methods are used.

- **`void execute()`**
  - Executes the main functionality of the library. This method should be called after initialization.

- **`void shutdown()`**
  - Shuts down the library and releases any resources that were allocated during its operation.

## Versioning

The library provides a function to retrieve the version information.

### Functions

- **`std::string getVersion()`**
  - Returns the version string of the library. This can be used to check the current version of the library in use.

## Usage Example

To use the library, include the necessary headers and follow these steps:

1. Include the core header:
   ```cpp
   #include "my_library/core.h"
   ```

2. Create an instance of the `Core` class and call its methods:
   ```cpp
   Core core;
   core.initialize();
   core.execute();
   core.shutdown();
   ```

3. To get the version of the library, include the version header:
   ```cpp
   #include "my_library/version.h"
   ```

4. Call the `getVersion()` function:
   ```cpp
   std::string version = getVersion();
   ```

## Conclusion

This API documentation provides a brief overview of the classes and methods available in the My C++ Library. For more detailed usage instructions, please refer to the getting started guide.