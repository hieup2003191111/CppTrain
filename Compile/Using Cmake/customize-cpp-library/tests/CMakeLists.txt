
# Download and link GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Include the main library directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the test executable
add_executable(test_core test_core.cpp)
target_link_libraries(test_core my_library GTest::gtest_main)

# Add the test executable for version
add_executable(test_version test_version.cpp)
target_link_libraries(test_version my_library GTest::gtest_main)

# Add tests to CMake
add_test(NAME TestCore COMMAND test_core)
add_test(NAME TestVersion COMMAND test_version)