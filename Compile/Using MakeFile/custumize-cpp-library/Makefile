# Makefile

CXX = g++
CXXFLAGS = -Iinclude -std=c++11 -Wall -Wextra
LIBRARY = libmy_library.a
SRC = src/core.cpp src/version.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean examples

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIBRARY)

examples:
	$(MAKE) -C examples
