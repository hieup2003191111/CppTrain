# Customizing C/C++ Libraries with Makefiles

## Slide 1: Introduction to C/C++ Libraries
- **What is a C/C++ Library?**
  - Reusable collections of code
  - Can be static (.a, .lib) or dynamic (.so, .dll)
  - Promotes code reuse and modular design
- **Benefits of Custom Libraries:**
  - Code encapsulation
  - Simplified maintenance
  - Easier collaboration
  - Version control

## Slide 2: Project Structure Overview
```
my-cpp-library/
├── Makefile           # Main Makefile
├── README.md          # Project documentation
├── examples/          # Example applications
│   ├── Makefile       # Makefile for examples
│   └── basic_usage.cpp # Example code
├── include/           # Public header files
│   └── my_library/
│       ├── core.h     # Core functionality headers
│       └── version.h  # Version information headers
└── src/               # Source files
    ├── core.cpp       # Core functionality implementation
    └── version.cpp    # Version information implementation
```

## Slide 3: Introduction to Makefiles
- **What is a Makefile?**
  - Build automation tool
  - Defines rules and dependencies
  - Avoids unnecessary recompilation
- **Basic Makefile Structure:**
  - Targets (what to build)
  - Dependencies (what files are needed)
  - Commands (how to build)
  - Variables (for reusable values)

## Slide 4: Key Makefile Concepts
- **Rules Format:**
  ```makefile
  target: dependencies
      commands
  ```
- **Variables:**
  ```makefile
  CXX = g++
  CXXFLAGS = -Wall -std=c++11
  ```
- **Phony Targets:**
  ```makefile
  .PHONY: clean all install
  ```
- **Automatic Variables:**
  - `$@`: Target name
  - `$<`: First dependency
  - `$^`: All dependencies

## Slide 5: Main Makefile Structure
```makefile
# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -fPIC

# Library name and versions
LIBRARY_NAME = my_library
VERSION = 1.0.0

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
LIBDIR = lib

# Files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
HEADERS = $(wildcard $(INCDIR)/$(LIBRARY_NAME)/*.h)

# Library files
STATIC_LIB = $(LIBDIR)/lib$(LIBRARY_NAME).a
SHARED_LIB = $(LIBDIR)/lib$(LIBRARY_NAME).so.$(VERSION)
SHARED_LIB_SHORT = $(LIBDIR)/lib$(LIBRARY_NAME).so

# Default target
all: static shared

# Create build directories
$(BUILDDIR) $(LIBDIR):
	mkdir -p $@

# Compile object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Build static library
static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJECTS) | $(LIBDIR)
	ar rcs $@ $^

# Build shared library
shared: $(SHARED_LIB)

$(SHARED_LIB): $(OBJECTS) | $(LIBDIR)
	$(CXX) -shared -Wl,-soname,lib$(LIBRARY_NAME).so -o $@ $^
	ln -sf $(notdir $(SHARED_LIB)) $(SHARED_LIB_SHORT)

# Clean build files
clean:
	rm -rf $(BUILDDIR) $(LIBDIR)

# Install the library
install: all
	install -d $(DESTDIR)/usr/local/lib
	install -d $(DESTDIR)/usr/local/include/$(LIBRARY_NAME)
	install -m 644 $(STATIC_LIB) $(DESTDIR)/usr/local/lib
	install -m 755 $(SHARED_LIB) $(DESTDIR)/usr/local/lib
	ln -sf $(notdir $(SHARED_LIB)) $(DESTDIR)/usr/local/lib/lib$(LIBRARY_NAME).so
	install -m 644 $(HEADERS) $(DESTDIR)/usr/local/include/$(LIBRARY_NAME)

# Define phony targets
.PHONY: all static shared clean install
```

## Slide 6: Examples Makefile Structure
```makefile
# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Directories
ROOTDIR = ..
INCDIR = $(ROOTDIR)/include
LIBDIR = $(ROOTDIR)/lib
BINDIR = bin

# Example source files
EXAMPLES = basic_usage

# Default target
all: $(EXAMPLES)

# Create output directory
$(BINDIR):
	mkdir -p $@

# Compile examples
%: %.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $< -L$(LIBDIR) -lmy_library -o $(BINDIR)/$@

# Clean build files
clean:
	rm -rf $(BINDIR)

# Define phony targets
.PHONY: all clean
```

## Slide 7: Header Files Structure
### `include/my_library/core.h`
```cpp
#ifndef MY_LIBRARY_CORE_H
#define MY_LIBRARY_CORE_H

namespace my_library {

// Core function declarations
void initialize();
int calculate(int a, int b);
void cleanup();

} // namespace my_library

#endif // MY_LIBRARY_CORE_H
```

### `include/my_library/version.h`
```cpp
#ifndef MY_LIBRARY_VERSION_H
#define MY_LIBRARY_VERSION_H

namespace my_library {

// Version information
struct Version {
    int major;
    int minor;
    int patch;
};

// Get library version
Version get_version();
const char* get_version_string();

} // namespace my_library

#endif // MY_LIBRARY_VERSION_H
```

## Slide 8: Implementation Files
### `src/core.cpp`
```cpp
#include "my_library/core.h"

namespace my_library {

void initialize() {
    // Initialization code
}

int calculate(int a, int b) {
    return a + b;
}

void cleanup() {
    // Cleanup code
}

} // namespace my_library
```

### `src/version.cpp`
```cpp
#include "my_library/version.h"
#include <string>

namespace my_library {

Version get_version() {
    return {1, 0, 0};
}

const char* get_version_string() {
    static std::string version = "1.0.0";
    return version.c_str();
}

} // namespace my_library
```

## Slide 9: Example Usage
### `examples/basic_usage.cpp`
```cpp
#include <iostream>
#include "my_library/core.h"
#include "my_library/version.h"

int main() {
    // Display version information
    auto version = my_library::get_version();
    std::cout << "Using my_library version: " 
              << version.major << "." 
              << version.minor << "." 
              << version.patch << std::endl;
    
    // Initialize the library
    my_library::initialize();
    
    // Use library functionality
    int result = my_library::calculate(5, 3);
    std::cout << "5 + 3 = " << result << std::endl;
    
    // Clean up
    my_library::cleanup();
    
    return 0;
}
```

## Slide 10: Building the Library
- **Building the Library:**
  ```bash
  # In the project root directory
  make all       # Build both static and shared libraries
  make static    # Build only static library
  make shared    # Build only shared library
  ```

- **Building and Running Examples:**
  ```bash
  # In the examples directory
  make all       # Build all examples
  ./bin/basic_usage  # Run the basic usage example
  ```

## Slide 11: Make Targets Explained
- **all**: Builds both static and shared libraries (default)
- **static**: Builds only the static library (.a)
- **shared**: Builds only the shared library (.so)
- **clean**: Removes all built files and directories
- **install**: Installs the library to the system

## Slide 12: Advanced Makefile Techniques
- **Pattern Rules**:
  ```makefile
  %.o: %.cpp
      $(CXX) $(CXXFLAGS) -c $< -o $@
  ```
  
- **Wildcards and Functions**:
  ```makefile
  SOURCES = $(wildcard $(SRCDIR)/*.cpp)
  OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
  ```
  
- **Conditional Logic**:
  ```makefile
  ifeq ($(OS),Windows_NT)
      # Windows-specific commands
  else
      # Unix-specific commands
  endif
  ```

## Slide 13: Library Versioning
- **Semantic Versioning**: MAJOR.MINOR.PATCH
  - MAJOR: Incompatible API changes
  - MINOR: Added functionality (backward compatible)
  - PATCH: Bug fixes (backward compatible)

- **Version Control in Makefiles**:
  ```makefile
  VERSION = 1.0.0
  SHARED_LIB = $(LIBDIR)/lib$(LIBRARY_NAME).so.$(VERSION)
  ```

## Slide 14: Static vs Shared Libraries
- **Static Libraries (.a, .lib)**:
  - Linked at compile time
  - Library code included in executable
  - No runtime dependencies
  - Larger executable size

- **Shared Libraries (.so, .dll)**:
  - Linked at runtime
  - Library code loaded as needed
  - Runtime dependencies
  - Smaller executable size

## Slide 15: Best Practices
- **Keep Makefiles Modular**
  - Separate main, examples, and test Makefiles
  - Use include directives for common definitions

- **Use Variables for Flexibility**
  - Define paths, compiler flags, and library names as variables

- **Add Helpful Documentation**
  - Comment complex parts of your Makefiles
  - Include usage instructions in README.md

- **Test Across Platforms**
  - Ensure Makefiles work on different operating systems
  - Use conditional logic for platform-specific settings

## Slide 16: Common Issues and Solutions
- **Library Not Found**: 
  - Ensure correct -L and -l flags
  - Set LD_LIBRARY_PATH for shared libraries

- **Undefined References**:
  - Check linking order
  - Verify all implementations are included

- **Recompiling Everything**:
  - Check dependency rules
  - Use proper pattern rules

- **Platform Compatibility**:
  - Use conditional compilation
  - Check for platform-specific tools

## Slide 17: Further Learning Resources
- **Official GNU Make Documentation**:
  - https://www.gnu.org/software/make/manual/

- **C++ Library Design Best Practices**:
  - https://isocpp.org/wiki/faq/

- **Advanced Makefile Techniques**:
  - http://makefiletutorial.com/

## Slide 18: Exercise
1. Add a new header file `math.h` and implementation file `math.cpp`
2. Implement basic math functions (add, subtract, multiply, divide)
3. Update the Makefile to include these new files
4. Create a new example that uses these math functions
5. Build and test your extended library

## Slide 19: Conclusion
- **Key Takeaways**:
  - Makefiles automate the build process
  - Library structure separates interface from implementation
  - Proper versioning helps manage dependencies
  - Both static and shared libraries have their uses

- **Next Steps**:
  - Add unit tests
  - Create documentation
  - Implement continuous integration
  - Add cross-platform support
