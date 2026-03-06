cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyCppLibraryExamples VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the library headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the example executable
add_executable(basic_usage basic_usage.cpp)

# Link the library to the example
target_link_libraries(basic_usage my_library)