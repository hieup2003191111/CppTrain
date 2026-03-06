# Hướng dẫn tạo Dynamic Library trong C/C++

## Giới thiệu

Dynamic Library (thư viện động) là một tập hợp các hàm được biên dịch và liên kết riêng biệt, được tải vào bộ nhớ khi chương trình cần chúng trong quá trình chạy. Thư viện động cho phép nhiều chương trình chia sẻ cùng một mã trong bộ nhớ, giúp tiết kiệm tài nguyên và dễ dàng cập nhật.

## Quy trình tạo Dynamic Library

### 1. Viết mã nguồn

Tương tự như static library, đầu tiên cần viết mã nguồn gồm:
- Header file (`.h`): Khai báo các hàm, class, struct, v.v.
- Source file (`.c`/`.cpp`): Triển khai các khai báo từ header file

#### Lưu ý quan trọng về Dynamic Library

Đối với dynamic library, cần phải chỉ rõ các hàm nào có thể được gọi từ bên ngoài thư viện. Đây gọi là "exporting symbols".

#### Trên Windows (MSVC):

```cpp
// my_library.h
#ifdef MY_LIBRARY_EXPORTS
#define MY_LIBRARY_API __declspec(dllexport)
#else
#define MY_LIBRARY_API __declspec(dllimport)
#endif

MY_LIBRARY_API int add(int a, int b);
```

#### Trên Linux/macOS (GCC/Clang):

```cpp
// my_library.h
#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef MY_LIBRARY_EXPORTS
    #define MY_LIBRARY_API __declspec(dllexport)
  #else
    #define MY_LIBRARY_API __declspec(dllimport)
  #endif
#else
  #define MY_LIBRARY_API __attribute__((visibility("default")))
#endif

MY_LIBRARY_API int add(int a, int b);
```

### 2. Biên dịch mã nguồn thành dynamic library

#### GCC/G++ (Linux/macOS)

```bash
g++ -shared -fPIC -o libmy_library.so my_library.cpp
```

#### MSVC (Windows)

```bash
cl /LD /DMY_LIBRARY_EXPORTS my_library.cpp /Femy_library.dll /link /OUT:my_library.dll
```

### 3. Sử dụng Dynamic Library trong chương trình

#### GCC/G++ (Linux/macOS)

```bash
g++ main.cpp -L. -lmy_library -Wl,-rpath=. -o my_program
```

#### MSVC (Windows)

```bash
cl main.cpp my_library.lib
```

## Tải Dynamic Library trong thời gian chạy (Dynamic Loading)

Một ưu điểm của dynamic library là có thể tải chúng vào chương trình trong thời gian chạy, không nhất thiết phải liên kết tĩnh khi biên dịch.

### Trên Windows:

```cpp
#include <windows.h>
#include <iostream>

int main() {
    // Tải thư viện
    HINSTANCE hinstLib = LoadLibrary(TEXT("my_library.dll"));
    
    if (hinstLib != NULL) {
        // Lấy địa chỉ hàm
        typedef int (*AddFunc)(int, int);
        AddFunc addFunc = (AddFunc)GetProcAddress(hinstLib, "add");
        
        if (addFunc != NULL) {
            // Gọi hàm
            int result = addFunc(5, 3);
            std::cout << "Result: " << result << std::endl;
        }
        
        // Giải phóng thư viện
        FreeLibrary(hinstLib);
    }
    return 0;
}
```

### Trên Linux/macOS:

```cpp
#include <dlfcn.h>
#include <iostream>

int main() {
    // Tải thư viện
    void* handle = dlopen("./libmy_library.so", RTLD_LAZY);
    
    if (handle != NULL) {
        // Lấy địa chỉ hàm
        typedef int (*AddFunc)(int, int);
        AddFunc addFunc = (AddFunc)dlsym(handle, "add");
        
        if (addFunc != NULL) {
            // Gọi hàm
            int result = addFunc(5, 3);
            std::cout << "Result: " << result << std::endl;
        }
        
        // Giải phóng thư viện
        dlclose(handle);
    }
    return 0;
}
```

## Sử dụng CMake để tạo Dynamic Library

Đây là một ví dụ về cách sử dụng CMake để tạo dynamic library:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

# Định nghĩa macro cho việc export symbols
add_definitions(-DMY_LIBRARY_EXPORTS)

# Tạo dynamic library
add_library(my_library SHARED
    src/my_library.cpp
)

# Thiết lập thư mục include
target_include_directories(my_library PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tạo executable
add_executable(my_program
    src/main.cpp
)

# Link thư viện với executable
target_link_libraries(my_program
    my_library
)
```

## Ưu và nhược điểm của Dynamic Library

### Ưu điểm

1. **Tiết kiệm không gian đĩa và bộ nhớ**: Nhiều ứng dụng có thể chia sẻ cùng một bản sao của thư viện
2. **Cập nhật dễ dàng**: Có thể cập nhật thư viện mà không cần biên dịch lại chương trình
3. **Tải theo yêu cầu**: Có thể tải các phần của thư viện khi cần thiết
4. **Plugin system**: Hỗ trợ việc phát triển các hệ thống plugin

### Nhược điểm

1. **DLL Hell/Dependency Hell**: Xung đột phiên bản giữa các thư viện
2. **Hiệu suất**: Chậm hơn static library do phải tải trong thời gian chạy và indirect calling
3. **Phức tạp hơn trong phân phối**: Phải đảm bảo thư viện được phân phối cùng chương trình

## Vấn đề thường gặp và giải pháp

### 1. DLL Hell/Dependency Hell

**Vấn đề**: Xung đột phiên bản giữa các thư viện.

**Giải pháp**:
- Sử dụng semantic versioning
- Đặt thư viện trong thư mục riêng của ứng dụng
- Sử dụng frameworks quản lý dependency

### 2. Tìm không thấy thư viện trong thời gian chạy

**Vấn đề**: Chương trình không thể tìm thấy thư viện khi chạy.

**Giải pháp**:
- Trên Windows: Đặt DLL trong cùng thư mục với executable hoặc thêm vào PATH
- Trên Linux: Sử dụng `-Wl,-rpath=$ORIGIN` khi liên kết
- Sử dụng biến môi trường như `LD_LIBRARY_PATH` (Linux) hoặc `DYLD_LIBRARY_PATH` (macOS)

### 3. Vấn đề ABI (Application Binary Interface)

**Vấn đề**: Thay đổi ABI có thể khiến cho chương trình không tương thích với phiên bản mới của thư viện.

**Giải pháp**:
- Duy trì tương thích ngược
- Sử dụng version numbers trong tên file thư viện
- Không thay đổi signature của hàm public

## Tham khảo thêm

- [Windows Dynamic-Link Libraries](https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-libraries)
- [Dynamic Linking in Linux and Windows](https://www.symantec.com/connect/articles/dynamic-linking-linux-and-windows-part-one)
