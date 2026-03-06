# Example of Dynamic Loading of Libraries

This is a supplementary example for the `dynamic_library` directory, illustrating how to load a Dynamic Library at runtime instead of statically linking it during compilation.

## Implementation on Windows:

```cpp
#include <windows.h>
#include <iostream>
#include <string>

typedef std::string (*ToUpperFunc)(const std::string&);
typedef std::string (*ToLowerFunc)(const std::string&);

int main() {
    std::cout << "Dynamic Loading Example (Windows)\n";
    std::cout << "--------------------------------\n";
    
    // Load the library
    HINSTANCE hinstLib = LoadLibrary(TEXT("string_utils.dll"));
    
    if (hinstLib == NULL) {
        std::cout << "Error: Could not load library\n";
        return 1;
    }
    
    // Get the address of the toUpper function
    ToUpperFunc toUpper = (ToUpperFunc)GetProcAddress(hinstLib, "?toUpper@stringutils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV23@@Z");
    
    if (toUpper == NULL) {
        std::cout << "Error: Could not find toUpper function\n";
        FreeLibrary(hinstLib);
        return 1;
    }
    
    // Get the address of the toLower function
    ToLowerFunc toLower = (ToLowerFunc)GetProcAddress(hinstLib, "?toLower@stringutils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV23@@Z");
    
    if (toLower == NULL) {
        std::cout << "Error: Could not find toLower function\n";
        FreeLibrary(hinstLib);
        return 1;
    }
    
    // Use the functions
    std::string text = "Hello, Dynamic Loading!";
    std::cout << "Original: " << text << std::endl;
    std::cout << "To Upper: " << toUpper(text) << std::endl;
    std::cout << "To Lower: " << toLower(text) << std::endl;
    
    // Free the library
    FreeLibrary(hinstLib);
    
    return 0;
}
```

Note: The mangled function names in the example above may differ depending on the compiler. You can use tools like `dumpbin` to see the actual names of exported functions:

```powershell
dumpbin /exports string_utils.dll
```

## Implementation on Linux:

```cpp
#include <dlfcn.h>
#include <iostream>
#include <string>

typedef std::string (*ToUpperFunc)(const std::string&);
typedef std::string (*ToLowerFunc)(const std::string&);

int main() {
    std::cout << "Dynamic Loading Example (Linux)\n";
    std::cout << "------------------------------\n";
    
    // Load the library
    void* handle = dlopen("./libstring_utils.so", RTLD_LAZY);
    
    if (handle == NULL) {
        std::cout << "Error: " << dlerror() << std::endl;
        return 1;
    }
    
    // Clear previous errors
    dlerror();
    
    // Get the address of the toUpper function
    ToUpperFunc toUpper = (ToUpperFunc)dlsym(handle, "_ZN11stringutils7toUpperERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE");
    
    char* error = dlerror();
    if (error != NULL) {
        std::cout << "Error getting toUpper: " << error << std::endl;
        dlclose(handle);
        return 1;
    }
    
    // Get the address of the toLower function
    ToLowerFunc toLower = (ToLowerFunc)dlsym(handle, "_ZN11stringutils7toLowerERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE");
    
    error = dlerror();
    if (error != NULL) {
        std::cout << "Error getting toLower: " << error << std::endl;
        dlclose(handle);
        return 1;
    }
    
    // Use the functions
    std::string text = "Hello, Dynamic Loading!";
    std::cout << "Original: " << text << std::endl;
    std::cout << "To Upper: " << toUpper(text) << std::endl;
    std::cout << "To Lower: " << toLower(text) << std::endl;
    
    // Free the library
    dlclose(handle);
    
    return 0;
}
```

Note: The mangled function names in the example above may differ depending on the compiler. You can use tools like `nm` to see the actual names of the functions:

```bash
nm -D libstring_utils.so | grep toUpper
```

## Better Solution: Using extern "C"

To avoid the name mangling issue, you can use `extern "C"` in the header file:

```cpp
// In string_utils.h
extern "C" {
    STRING_UTILS_API std::string stringutils_toUpper(const std::string& input);
    STRING_UTILS_API std::string stringutils_toLower(const std::string& input);
    // ... other functions
}
```

This way, the functions will have simpler names and be easier to use with dynamic loading:

```cpp
// Windows
ToUpperFunc toUpper = (ToUpperFunc)GetProcAddress(hinstLib, "stringutils_toUpper");

// Linux
ToUpperFunc toUpper = (ToUpperFunc)dlsym(handle, "stringutils_toUpper");
```

## Conclusion

Dynamic loading allows you to load and use libraries at runtime, providing greater flexibility compared to static linking. However, it is also more complex and may encounter difficulties with issues like name mangling. In practical applications, using `extern "C"` or designing an API suitable for dynamic loading is very important.
