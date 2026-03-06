# CMakeLists.txt cho Combined Static and Dynamic Library Example
cmake_minimum_required(VERSION 3.10)
project(CombinedLibrariesExample)

# Thiết lập C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Định nghĩa macro cho việc export symbols của dynamic library
add_definitions(-DSTRING_UTILS_EXPORTS)

# Tạo static library
add_library(math_library STATIC
    math_library.cpp
)

# Tạo dynamic library
add_library(string_utils SHARED
    string_utils.cpp
)

# Thiết lập thuộc tính cho dynamic library
set_target_properties(string_utils PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

# Trên Windows, thêm các file .lib và .dll vào thư mục output
if(WIN32)
    set_target_properties(string_utils PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()

# Tạo executable sử dụng cả hai thư viện
add_executable(combined_program
    main.cpp
)

# Link cả static và dynamic library với executable
target_link_libraries(combined_program
    math_library
    string_utils
)

# Thêm README để giải thích cách build và chạy
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/README.md.in
               ${CMAKE_CURRENT_BINARY_DIR}/README.md @ONLY)