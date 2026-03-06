cmake_minimum_required(VERSION 3.11)

project(MyCppLibrary VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(my_library src/core.cpp src/version.cpp)

add_executable(example examples/basic_usage.cpp)
target_link_libraries(example my_library)

enable_testing()
add_subdirectory(tests)