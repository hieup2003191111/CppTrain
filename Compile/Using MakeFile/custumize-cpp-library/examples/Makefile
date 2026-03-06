# Makefile for the C++ Library

# Define the compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -std=c++11

# Define the library name
LIBRARY = my_library
LIBRARY_SRC = src/core.cpp src/version.cpp
LIBRARY_OBJ = $(LIBRARY_SRC:.cpp=.o)

# Define the example executables
EXAMPLES = basic_usage
EXAMPLE_SRC = examples/basic_usage.cpp
EXAMPLE_OBJ = $(EXAMPLE_SRC:.cpp=.o)

# Default target
all: $(LIBRARY) $(EXAMPLES)

# Build the library
$(LIBRARY): $(LIBRARY_OBJ)
	$(CXX) -shared -o lib$(LIBRARY).so $(LIBRARY_OBJ)

# Build the examples
basic_usage: $(EXAMPLE_OBJ) $(LIBRARY)
	$(CXX) -o $@ $^ -L. -l$(LIBRARY)

# Clean up build artifacts
clean:
	rm -f $(LIBRARY_OBJ) $(EXAMPLE_OBJ) $(EXAMPLES) lib$(LIBRARY).so

# Phony targets
.PHONY: all clean