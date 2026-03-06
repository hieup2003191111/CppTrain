# Static and Dynamic Libraries in C/C++ Using Makefile
## A Comprehensive Guide

---

# Table of Contents

1. **Introduction to Libraries in C/C++**
2. **Static Libraries**
3. **Dynamic Libraries**
4. **Comparison between Static and Dynamic Libraries**
5. **Creating and Using Libraries**
6. **Makefile for Library Development**
7. **Advanced Topics**
8. **Practical Exercises**
9. **Common Issues and Solutions**

---

# 1. Introduction to Libraries in C/C++

---

## 1.1 What are Libraries?

- Collections of pre-compiled code that can be reused across multiple programs
- Encapsulate functionality in a modular, reusable format
- Allow code sharing and modular software development
- Can be provided by the language, third parties, or developed in-house

---

## 1.2 Benefits of Using Libraries

- **Code Reusability**: Write once, use many times
- **Modularity**: Break complex applications into manageable components
- **Maintainability**: Update implementations without changing client code
- **Collaboration**: Multiple developers can work on different components
- **Specialization**: Use expert-developed code for specific domains

---

## 1.3 Types of Libraries

- **Standard Libraries**: Come with the language (e.g., `stdio.h`, `stdlib.h`)
- **Third-Party Libraries**: Developed by other organizations (e.g., Boost, Qt)
- **Custom Libraries**: Developed in-house for specific projects
- **Based on Linking**: Static Libraries and Dynamic Libraries

---

# 2. Static Libraries

---

## 2.1 What are Static Libraries?

- Collections of object files that are linked directly into the executable at compile time
- File extensions:
  - `.a` (archive) on Linux/Unix/MinGW
  - `.lib` on Windows with MSVC
- Become part of the executable file

---

## 2.2 How Static Libraries Work

- Object files from the library are copied into the final executable during linking
- No external dependencies required at runtime
- Each program using the library has its own copy of the library code

---

## 2.3 Advantages of Static Libraries

- **Self-contained executables**: No external library dependencies
- **Stability**: No version compatibility issues
- **Performance**: No runtime loading overhead
- **Optimization**: Compiler can optimize across library boundaries
- **Simplicity**: Easier deployment, no need to distribute separate library files

---

## 2.4 Disadvantages of Static Libraries

- **Larger executable size**: Library code is embedded in each program
- **Memory inefficiency**: Multiple running programs duplicate library code in memory
- **Update challenges**: Requires recompiling all applications when library changes
- **Limited sharing**: Each program has its own copy

---

# 3. Dynamic Libraries

---

## 3.1 What are Dynamic Libraries?

- Libraries that are loaded into memory at runtime
- File extensions:
  - `.so` (shared object) on Linux/Unix
  - `.dll` (dynamic-link library) on Windows
  - `.dylib` on macOS
- Exist as separate files from the executable

---

## 3.2 How Dynamic Libraries Work

- Executables contain references to the library
- The operating system loads the library into memory when the program starts
- Multiple programs can share a single copy of the library in memory
- Libraries can be updated without recompiling applications

---

## 3.3 Advantages of Dynamic Libraries

- **Smaller executable size**: Library code not embedded in executable
- **Memory efficiency**: Multiple programs share one copy in memory
- **Easy updates**: Library can be updated without recompiling applications
- **Runtime flexibility**: Libraries can be loaded/unloaded on demand
- **Plugin architecture**: Supports extensible software design

---

## 3.4 Disadvantages of Dynamic Libraries

- **External dependencies**: Library must be available at runtime
- **Version conflicts**: Potential "DLL Hell" or incompatibilities
- **Slightly slower startup**: Time needed to load libraries
- **Deployment complexity**: Need to ensure correct libraries are installed

---

# 4. Comparison between Static and Dynamic Libraries

---

## 4.1 Feature Comparison

| Feature | Static Libraries | Dynamic Libraries |
|---------|-----------------|-------------------|
| **File Size** | Larger executables | Smaller executables |
| **Loading Time** | Faster | Slightly slower (load time) |
| **Runtime Dependencies** | None | Library files required |
| **Memory Usage** | Higher (multiple copies) | Lower (shared in memory) |
| **Updates** | Requires recompilation | Just replace library file |
| **Optimization** | Better cross-module optimization | Limited to library boundaries |

---

## 4.2 When to Use Static Libraries

- Small, standalone applications
- Embedded systems with limited resources
- Applications where performance is critical
- When you want to avoid dependency and versioning issues
- Applications that need to be portable without dependencies

---

## 4.3 When to Use Dynamic Libraries

- Large systems with multiple applications using the same library
- When frequent updates are expected without rebuilding applications
- When working with plugins or extensible architectures
- When executable size is a concern
- When memory efficiency across multiple processes is important

---

# 5. Creating and Using Libraries

---

## 5.1 Project Structure

```
project/
├── include/      # Header files (.h)
├── src/          # Source files (.c/.cpp)
├── obj/          # Object files (.o)
├── lib/          # Library files (.a/.dll/.so)
├── bin/          # Executable files
├── main.c        # Test application
└── Makefile      # Build automation
```

---

## 5.2 Header Files

```c
// include/mylib.h
#ifndef MYLIB_H
#define MYLIB_H

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define MYLIB_API __declspec(dllexport)
    #else


    #endif

MYLIB_API int add(int a, int b);
MYLIB_API int subtract(int a, int b);



---

## 5.3 Implementation Files

```c
// src/mylib.c
#include <stdio.h>
#include "../include/mylib.h"

#ifdef _WIN32
    #define BUILDING_DLL
#endif

void hello() {
    printf("Hello from library!\n");
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
```

---

## 5.4 Creating a Static Library

### Linux/MinGW

```bash
# Compile source files to object files
gcc -c -o mylib.o mylib.c

# Create archive
ar rcs libmylib.a mylib.o
```

### Windows (MSVC)

```bash
# Compile source files to object files
cl /c mylib.c

# Create library
lib /OUT:mylib.lib mylib.obj
```

---

## 5.5 Creating a Dynamic Library

### Linux

```bash
# Create shared library
gcc -shared -fPIC -o libmylib.so mylib.c
```

### Windows (MinGW)

```bash
# Create DLL
gcc -shared -o mylib.dll mylib.c -Wl,--out-implib,libmylib.a
```

### Windows (MSVC)

```bash
# Create DLL
cl /LD mylib.c /Fe:mylib.dll
```

---

## 5.6 Using a Static Library

### Linux/MinGW

```bash
# Compile with static library
gcc main.c -L. -lmylib -o main_static
```

### Windows (MSVC)

```bash
# Compile with static library
cl main.c mylib.lib /Fe:main_static.exe
```

---

## 5.7 Using a Dynamic Library

### Linux

```bash
# Compile with dynamic library
gcc main.c -L. -lmylib -o main_dynamic

# Run (make sure library is in path)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./main_dynamic
```

### Windows

```bash
# Compile with dynamic library
gcc main.c -L. -lmylib -o main_dynamic.exe

# Run (make sure DLL is in PATH or same directory)
main_dynamic.exe
```

---

## 5.8 Testing the Library

```c
// main.c
#include <stdio.h>
#include "include/mylib.h"

int main() {
    hello();
    
    int result1 = add(10, 5);
    int result2 = subtract(10, 5);
    
    printf("10 + 5 = %d\n", result1);
    printf("10 - 5 = %d\n", result2);
    
    return 0;
}
```

---

# 6. Makefile for Library Development

---

## 6.1 Introduction to Makefile

- Text file containing rules for building software
- Used by the `make` command-line utility
- Automates complex build processes
- Selective recompilation based on file changes
- Manages dependencies between source files

---

## 6.2 Basic Makefile Syntax

```makefile
target: dependencies
    commands
```

- **target**: The file to be created or action to perform
- **dependencies**: Files needed before creating target
- **commands**: Shell commands to execute (must be indented with TAB, not spaces)

---

## 6.3 Variables in Makefile

```makefile
CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
OBJ_DIR = obj

# Usage
$(CC) $(CFLAGS) -c $< -o $@
```

---

## 6.4 Special Variables

- `$@`: Target name
- `$<`: First dependency
- `$^`: All dependencies
- `$*`: Target name without extension

```makefile
hello: hello.c helper.c
    $(CC) -o $@ $^  # Expands to: gcc -o hello hello.c helper.c
```

---

## 6.5 Functions in Makefile

```makefile
# Find all .c files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Convert from .c to .o
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Execute shell command
$(shell if not exist $(OBJ_DIR) mkdir $(OBJ_DIR))
```

---

## 6.6 Makefile for Static and Dynamic Libraries

```makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iinclude
# Flag cho PIC
PICFLAGS = -fPIC

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

# Create directories if they don't exist
$(shell if not exist $(OBJ_DIR) mkdir $(OBJ_DIR))
$(shell if not exist $(LIB_DIR) mkdir $(LIB_DIR))

# Library names
LIB_NAME = mylib
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
DYNAMIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).so

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
PIC_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.pic.o,$(SRCS))
```

---

## 6.7 Rules for Building Libraries

```makefile
# Default target
all: static dynamic

# Compile source to object files (static)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
  $(CC) $(CFLAGS) -c $< -o $@

# Compile source to PIC object files (dynamic)
$(OBJ_DIR)/%.pic.o: $(SRC_DIR)/%.c
  $(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

# Static library
static: $(OBJS)
  ar rcs $(STATIC_LIB) $(OBJS)
  @echo Static library created: $(STATIC_LIB)

# Dynamic library
dynamic: $(PIC_OBJS)
  $(CC) -shared -o $(DYNAMIC_LIB) $(PIC_OBJS) $(CFLAGS)
  @echo Dynamic library created: $(DYNAMIC_LIB)
```

---

## 6.8 Rules for Building Applications

```makefile
# Application with static library
main_static: static
	$(CC) main.c -L$(LIB_DIR) -l$(LIB_NAME) -o bin/main_static.exe $(CFLAGS)

# Application with dynamic library
main_dynamic: dynamic
	$(CC) main.c -L$(LIB_DIR) -l$(LIB_NAME) -o bin/main_dynamic.exe $(CFLAGS)
	@echo Note: Make sure $(LIB_DIR) is in PATH or copy DLL to executable directory

# Clean up
clean:
	-del /Q $(OBJ_DIR)\*.o $(LIB_DIR)\*.a $(LIB_DIR)\*.dll bin\*.exe 2>NUL

.PHONY: all static dynamic clean
```

---

# 7. Advanced Topics

---

## 7.1 Symbol Visibility

### Windows

```c
// Export symbols in DLL
__declspec(dllexport) int add(int a, int b);

// Import symbols from DLL
__declspec(dllimport) int add(int a, int b);
```

### Linux

```c
// GCC specific attribute
__attribute__((visibility("default"))) int add(int a, int b);
```

---

## 7.2 Dynamic Loading

### Linux

```c
#include <dlfcn.h>

// Open library
void* handle = dlopen("./libmylib.so", RTLD_LAZY);

// Get function pointer
int (*add)(int, int) = dlsym(handle, "add");

// Use function
int result = add(5, 3);

// Close library
dlclose(handle);
```

---

## 7.2 Dynamic Loading (continued)

### Windows

```c
#include <windows.h>

// Load library
HINSTANCE lib = LoadLibrary("mylib.dll");

// Get function pointer
typedef int (*AddFunc)(int, int);
AddFunc add = (AddFunc)GetProcAddress(lib, "add");

// Use function
int result = add(5, 3);

// Free library
FreeLibrary(lib);
```

---

## 7.3 Versioning in Shared Libraries

### Linux

```bash
# Create with version info
gcc -shared -Wl,-soname,libmylib.so.1 -o libmylib.so.1.0.0 *.o

# Create symlinks
ln -sf libmylib.so.1.0.0 libmylib.so.1
ln -sf libmylib.so.1 libmylib.so
```

---

## 7.4 Debugging Libraries

- Use `-g` flag when compiling libraries
- For dynamic libraries:
  - Linux: Use `ldd` to check dependencies
  - Windows: Use `Dependency Walker`
- Use tools like `nm` (Linux) to inspect symbols
- Environment variables:
  - Linux: `LD_DEBUG=all`
  - Windows: `set PATH` to verify DLL search paths

---

# 8. Practical Exercises

---

## Exercise 1: Math Library

Create a library `mathlib` with the following functions:
- `int add(int a, int b)`
- `int subtract(int a, int b)`
- `int multiply(int a, int b)`
- `float divide(int a, int b)`
- `double power(double base, int exponent)`
- `double square_root(double x)`

Build both static and dynamic versions and create a test program.

---

## Exercise 2: String Library

Create a library `strlib` with the following functions:
- `char* str_reverse(const char* str)`
- `char* str_to_upper(const char* str)`
- `char* str_to_lower(const char* str)`
- `int str_count(const char* str, char c)`
- `char* str_trim(const char* str)`

Build both static and dynamic versions and create a test program.

---

## Exercise 3: Array Processing Library

Create a library `arraylib` with the following functions:
- `void sort_array(int arr[], int size, int ascending)`
- `int find_element(int arr[], int size, int element)`
- `float average(int arr[], int size)`
- `int max_element(int arr[], int size)`
- `int min_element(int arr[], int size)`

Build both static and dynamic versions and create a test program.

---

## Exercise 4: File Processing Library

Create a library `filelib` with the following functions:
- `int count_lines(const char* filename)`
- `int count_words(const char* filename)`
- `int search_string(const char* filename, const char* str)`
- `int copy_file(const char* source, const char* destination)`
- `int merge_files(const char* file1, const char* file2, const char* destination)`

Build both static and dynamic versions and create a test program.

---

# 9. Common Issues and Solutions

---

## 9.1 Library Not Found

### Issue:
```
error while loading shared libraries: libmylib.so: cannot open shared object file: No such file or directory
```

### Solutions:
- **Linux:** Add library path to `LD_LIBRARY_PATH`
  ```bash
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/lib
  ```
- **Windows:** Put DLL in executable directory or add to PATH
  ```powershell
  $env:PATH += ";C:\path\to\lib"
  ```

---

## 9.2 Undefined Reference

### Issue:
```
undefined reference to 'function_name'
```

### Solutions:
- Check function name spelling (case-sensitive)
- Ensure the library contains the function definition
- Check library linking order (dependencies first)
- Verify export/import macros are correctly used

---

## 9.3 Multiple Definition

### Issue:
```
multiple definition of 'function_name'
```

### Solutions:
- Use proper header guards in all header files
- Avoid global variables in header files (use extern)
- Use static for functions meant to be internal
- Check for duplicate function implementations

---

## 9.4 DLL Hell (Version Conflicts)

### Issue:
Application breaks when another application installs a different version of a shared library.

### Solutions:
- Use static linking for critical dependencies
- Implement versioning in your libraries
- Use side-by-side assemblies (Windows)
- Distribute libraries with your application in a private directory

---

## 9.5 Makefile Errors

### Issue:
```
Makefile:3: *** missing separator. Stop.
```

### Solutions:
- Use tabs, not spaces, for command indentation
- Check for syntax errors in Makefile
- Verify all dependencies exist or can be created
- Use $(wildcard ...) to avoid errors with missing files

---

# Thank You!

## Additional Resources

- [GNU Make Manual](https://www.gnu.org/software/make/manual/)
- [Advanced C and C++ Compiling](https://www.apress.com/gp/book/9781430266679)
- [Linux Foundation Course on Shared Libraries](https://training.linuxfoundation.org/training/developing-shared-libraries/)
- [Microsoft Documentation on DLLs](https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-libraries)

---

# Appendix: Complete Makefile

```makefile
# Makefile for building static and dynamic libraries
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

# Create directories if they don't exist
$(shell if not exist $(OBJ_DIR) mkdir $(OBJ_DIR))
$(shell if not exist $(LIB_DIR) mkdir $(LIB_DIR))
$(shell if not exist $(BIN_DIR) mkdir $(BIN_DIR))

# Library name
LIB_NAME = mylib
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
DYNAMIC_LIB = $(LIB_DIR)/$(LIB_NAME).dll

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Default target
all: static dynamic main_static main_dynamic

# Create directories
directories:
	-mkdir $(OBJ_DIR) 2>NUL
	-mkdir $(LIB_DIR) 2>NUL
	-mkdir $(BIN_DIR) 2>NUL

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library
static: directories $(OBJ_FILES)
	ar rcs $(STATIC_LIB) $(OBJ_FILES)
	@echo Static library created: $(STATIC_LIB)

# Create dynamic library
dynamic: directories $(SRC_FILES)
	$(CC) -shared -o $(DYNAMIC_LIB) $(SRC_FILES) $(CFLAGS)
	@echo Dynamic library created: $(DYNAMIC_LIB)

# Build application with static library
main_static: static
	$(CC) main.c -L$(LIB_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/main_static.exe $(CFLAGS)
	@echo Static executable created: $(BIN_DIR)/main_static.exe

# Build application with dynamic library
main_dynamic: dynamic
	$(CC) main.c -L$(LIB_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/main_dynamic.exe $(CFLAGS)
	@echo Dynamic executable created: $(BIN_DIR)/main_dynamic.exe
	@echo Note: Make sure $(LIB_DIR) is in your PATH or copy $(DYNAMIC_LIB) to the same directory as the executable

# Clean up
clean:
	-del /Q $(OBJ_DIR)\*.o 2>NUL
	-del /Q $(LIB_DIR)\*.a 2>NUL
	-del /Q $(LIB_DIR)\*.dll 2>NUL
	-del /Q $(BIN_DIR)\*.exe 2>NUL

.PHONY: all clean static dynamic main_static main_dynamic directories
```
