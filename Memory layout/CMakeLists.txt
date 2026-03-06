cmake_minimum_required(VERSION 3.10)
project(MemoryLayout VERSION 1.0)

# Yêu cầu chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Thêm thư mục include
include_directories(${PROJECT_SOURCE_DIR}/include)

# Tạo executable cho từng ví dụ
add_executable(example1 src/example1_variables.cpp)
add_executable(example2 src/example2_dynamic_memory.cpp)
add_executable(example3 src/example3_memory_analysis.cpp)
add_executable(example4 src/example4_memory_issues.cpp)

# Tùy chọn biên dịch
if(MSVC)
    # Tùy chọn cho trình biên dịch Visual C++
    target_compile_options(example1 PRIVATE /W4)
    target_compile_options(example2 PRIVATE /W4)
    target_compile_options(example3 PRIVATE /W4)
    target_compile_options(example4 PRIVATE /W4)
else()
    # Tùy chọn cho GCC/Clang
    target_compile_options(example1 PRIVATE -Wall -Wextra)
    target_compile_options(example2 PRIVATE -Wall -Wextra)
    target_compile_options(example3 PRIVATE -Wall -Wextra)
    target_compile_options(example4 PRIVATE -Wall -Wextra)
endif()

# Tùy chọn để enable sanitizer (nếu được hỗ trợ)
option(ENABLE_SANITIZER "Enable Address Sanitizer" OFF)
if(ENABLE_SANITIZER)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(example2 PRIVATE -fsanitize=address)
        target_compile_options(example4 PRIVATE -fsanitize=address)
        target_link_options(example2 PRIVATE -fsanitize=address)
        target_link_options(example4 PRIVATE -fsanitize=address)
    endif()
endif()

# Tạo một target "all_examples" để build tất cả các ví dụ
add_custom_target(all_examples 
    DEPENDS example1 example2 example3 example4
    COMMENT "Build all examples")

# Hiển thị hướng dẫn sau khi build
add_custom_command(TARGET all_examples POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "All examples built successfully. Run them individually:"
    COMMAND ${CMAKE_COMMAND} -E echo "  example1 - Basic memory layout demonstration"
    COMMAND ${CMAKE_COMMAND} -E echo "  example2 - Dynamic memory allocation demonstration"
    COMMAND ${CMAKE_COMMAND} -E echo "  example3 - Detailed memory analysis"
    COMMAND ${CMAKE_COMMAND} -E echo "  example4 - Common memory issues and solutions"
)
