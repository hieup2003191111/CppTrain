# CMakeLists.txt cho Static Library Example
cmake_minimum_required(VERSION 3.10)
project(MathLibraryStatic)

# Thiết lập C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tạo static library
add_library(math_library STATIC
    math_library.cpp
)

# Tạo executable
add_executable(math_program
    main.cpp
)

# Link thư viện với executable
target_link_libraries(math_program
    math_library
)

# Thêm README để giải thích cách build và chạy
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/README.md.in
               ${CMAKE_CURRENT_BINARY_DIR}/README.md @ONLY)
