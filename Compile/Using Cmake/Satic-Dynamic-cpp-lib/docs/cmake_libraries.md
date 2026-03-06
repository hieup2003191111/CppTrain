# Sử dụng CMake để quản lý Static và Dynamic Library

## Giới thiệu

CMake là một công cụ đa nền tảng để tự động hóa quá trình xây dựng (build) phần mềm. Nó đặc biệt hữu ích khi làm việc với các thư viện vì nó giúp quản lý các thư viện một cách độc lập với nền tảng và compiler.

## Cài đặt CMake

### Windows

1. Tải CMake từ [trang chủ](https://cmake.org/download/)
2. Chạy installer và làm theo hướng dẫn
3. Thêm CMake vào PATH

### Linux

```bash
sudo apt-get install cmake  # Debian/Ubuntu
sudo yum install cmake      # CentOS/RHEL
sudo dnf install cmake      # Fedora
```

### macOS

```bash
brew install cmake
```

## Tạo Static Library với CMake

Dưới đây là một ví dụ cơ bản về cách tạo một static library với CMake:

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyStaticLib)

# Tạo static library
add_library(my_static_lib STATIC
    src/function1.cpp
    src/function2.cpp
)

# Thiết lập thư mục include
target_include_directories(my_static_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Thiết lập thuộc tính khác
set_target_properties(my_static_lib PROPERTIES
    OUTPUT_NAME "my_lib"  # Tên của file output (libmy_lib.a hoặc my_lib.lib)
)

# Tạo executable sử dụng thư viện
add_executable(my_program
    src/main.cpp
)

# Link thư viện với executable
target_link_libraries(my_program
    my_static_lib
)
```

## Tạo Dynamic Library với CMake

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyDynamicLib)

# Định nghĩa macro cho việc export symbols
add_definitions(-DMY_LIBRARY_EXPORTS)

# Tạo dynamic library
add_library(my_dynamic_lib SHARED
    src/function1.cpp
    src/function2.cpp
)

# Thiết lập thư mục include
target_include_directories(my_dynamic_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Thiết lập thuộc tính
set_target_properties(my_dynamic_lib PROPERTIES
    OUTPUT_NAME "my_lib"
    VERSION 1.0.0
    SOVERSION 1
)

# Tạo executable
add_executable(my_program
    src/main.cpp
)

# Link thư viện với executable
target_link_libraries(my_program
    my_dynamic_lib
)
```

## Tạo cả Static và Dynamic Library từ cùng mã nguồn

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

# Các source file chung
set(SOURCES
    src/function1.cpp
    src/function2.cpp
)

# Tạo static library
add_library(my_static_lib STATIC ${SOURCES})
set_target_properties(my_static_lib PROPERTIES
    OUTPUT_NAME "my_lib"
)

# Tạo dynamic library
add_library(my_dynamic_lib SHARED ${SOURCES})
target_compile_definitions(my_dynamic_lib PRIVATE -DMY_LIBRARY_EXPORTS)
set_target_properties(my_dynamic_lib PROPERTIES
    OUTPUT_NAME "my_lib"
    VERSION 1.0.0
    SOVERSION 1
)

# Thiết lập thư mục include cho cả hai thư viện
target_include_directories(my_static_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(my_dynamic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Tạo executable sử dụng static library
add_executable(static_program src/main.cpp)
target_link_libraries(static_program my_static_lib)

# Tạo executable sử dụng dynamic library
add_executable(dynamic_program src/main.cpp)
target_link_libraries(dynamic_program my_dynamic_lib)
```

## Sử dụng thư viện bên ngoài với CMake

### Tìm và sử dụng thư viện đã cài đặt

```cmake
# Tìm thư viện
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Link thư viện với target
target_link_libraries(my_program
    Boost::filesystem
    Boost::system
)
```

### Tự động tải và build thư viện bên ngoài

```cmake
include(FetchContent)

# Khai báo dependency
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

# Tải và build
FetchContent_MakeAvailable(json)

# Link thư viện
target_link_libraries(my_program
    nlohmann_json::nlohmann_json
)
```

## Cấu hình Xây dựng

### Debug và Release

```cmake
# Thiết lập flags biên dịch cho các chế độ khác nhau
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
```

Khi build:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
# hoặc
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### Xây dựng trên các nền tảng khác nhau

CMake giúp xây dựng project trên nhiều nền tảng khác nhau:

```bash
# Windows với Visual Studio
cmake -G "Visual Studio 16 2019" -A x64 ..

# Linux/macOS với Makefiles
cmake -G "Unix Makefiles" ..

# Ninja build system
cmake -G "Ninja" ..
```

## Cài đặt thư viện

```cmake
# Cài đặt thư viện
install(TARGETS my_static_lib my_dynamic_lib
    ARCHIVE DESTINATION lib  # Static libraries
    LIBRARY DESTINATION lib  # Dynamic libraries
    RUNTIME DESTINATION bin  # Windows DLLs
)

# Cài đặt header files
install(DIRECTORY include/
    DESTINATION include
)
```

Để cài đặt:
```bash
cmake --build . --target install
```

## Tích hợp với IDE

### Visual Studio Code

1. Cài đặt extension "CMake Tools" và "C/C++"
2. Mở thư mục project
3. Chọn compiler và build configuration từ status bar

### Visual Studio

1. Mở project với "Open Folder"
2. Visual Studio sẽ tự động phát hiện CMakeLists.txt
3. Sử dụng CMake menu để configure và build

### CLion

CLion hỗ trợ CMake natively. Chỉ cần mở thư mục chứa CMakeLists.txt.

## Thực hành tốt nhất

1. **Sử dụng target_include_directories, target_compile_definitions, và target_link_libraries** thay vì include_directories, add_definitions, và link_libraries
2. **Tạo các config file** để xuất các biến số và đường dẫn cần thiết
3. **Sử dụng find_package** thay vì tự tìm thư viện
4. **Thiết lập version** cho thư viện của bạn
5. **Tạo và chạy tests** với CTest

## Tham khảo thêm

- [CMake Documentation](https://cmake.org/documentation/)
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [CMake Examples](https://github.com/ttroy50/cmake-examples)
