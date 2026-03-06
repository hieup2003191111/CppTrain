# CMakeLists.txt cho Singleton Examples
cmake_minimum_required(VERSION 3.10)
project(SingletonExamples VERSION 1.0 LANGUAGES CXX)

# Yêu cầu C++17 (hoặc C++11/14 cũng được)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thêm warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Example 1: Basic Singleton
add_executable(singleton_basic singleton_basic.cpp)

# Example 2: Embedded Singleton
add_executable(singleton_embedded singleton_embedded.cpp)

# Thêm pthread cho Linux/Mac (cần cho std::mutex)
if(NOT MSVC)
    find_package(Threads REQUIRED)
    target_link_libraries(singleton_basic Threads::Threads)
    target_link_libraries(singleton_embedded Threads::Threads)
endif()

# Thông báo hướng dẫn build
message(STATUS "")
message(STATUS "=== Singleton Examples ===")
message(STATUS "Để build và chạy:")
message(STATUS "  mkdir build && cd build")
message(STATUS "  cmake ..")
message(STATUS "  cmake --build .")
message(STATUS "  ./singleton_basic")
message(STATUS "  ./singleton_embedded")
message(STATUS "")
