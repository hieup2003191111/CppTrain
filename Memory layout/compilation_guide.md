# Hướng dẫn biên dịch và chạy các ví dụ

Tài liệu này cung cấp hướng dẫn biên dịch và chạy các ví dụ về bố cục bộ nhớ trong C/C++ được cung cấp trong thư mục `src/`.

## Yêu cầu

- Trình biên dịch C++ hỗ trợ chuẩn C++11 trở lên (GCC, Clang, hoặc MSVC)
- CMake (tùy chọn, nếu bạn muốn sử dụng CMakeLists.txt đi kèm)

## Biên dịch bằng trình biên dịch trực tiếp

### Windows (với MSVC)

Sử dụng Developer Command Prompt for VS:

```bash
# Biên dịch ví dụ 1
cl /EHsc /std:c++17 src\example1_variables.cpp /Fe:example1.exe

# Biên dịch ví dụ 2
cl /EHsc /std:c++17 src\example2_dynamic_memory.cpp /Fe:example2.exe

# Biên dịch ví dụ 3
cl /EHsc /std:c++17 src\example3_memory_analysis.cpp /Fe:example3.exe

# Biên dịch ví dụ 4
cl /EHsc /std:c++17 src\example4_memory_issues.cpp /Fe:example4.exe
```

### Windows (với MinGW/GCC)

```bash
# Biên dịch ví dụ 1
g++ -std=c++17 src\example1_variables.cpp -o example1.exe

# Biên dịch ví dụ 2
g++ -std=c++17 src\example2_dynamic_memory.cpp -o example2.exe

# Biên dịch ví dụ 3
g++ -std=c++17 src\example3_memory_analysis.cpp -o example3.exe

# Biên dịch ví dụ 4
g++ -std=c++17 src\example4_memory_issues.cpp -o example4.exe
```

### Linux/Mac (với GCC/Clang)

```bash
# Biên dịch ví dụ 1
g++ -std=c++17 src/example1_variables.cpp -o example1

# Biên dịch ví dụ 2
g++ -std=c++17 src/example2_dynamic_memory.cpp -o example2

# Biên dịch ví dụ 3
g++ -std=c++17 src/example3_memory_analysis.cpp -o example3

# Biên dịch ví dụ 4
g++ -std=c++17 src/example4_memory_issues.cpp -o example4
```

## Biên dịch với CMake

Dự án này cũng cung cấp CMakeLists.txt để dễ dàng biên dịch với CMake:

```bash
# Tạo thư mục build
mkdir build
cd build

# Cấu hình CMake
cmake ..

# Biên dịch
cmake --build .
```

## Chạy các ví dụ

Sau khi biên dịch, bạn có thể chạy các ví dụ như sau:

### Windows

```bash
# Chạy từng ví dụ
example1.exe
example2.exe
example3.exe
example4.exe
```

### Linux/Mac

```bash
# Chạy từng ví dụ
./example1
./example2
./example3
./example4
```

## Chạy ví dụ với Valgrind (Linux)

Để kiểm tra memory leak trong các ví dụ, bạn có thể sử dụng Valgrind:

```bash
# Cài đặt Valgrind (nếu chưa có)
sudo apt-get install valgrind   # Ubuntu/Debian
sudo yum install valgrind       # CentOS/RHEL

# Chạy kiểm tra memory leak
valgrind --leak-check=full ./example2
valgrind --leak-check=full ./example4
```

## Các công cụ khác để phân tích bộ nhớ

### Windows
- Visual Studio Memory Profiler
- Dr. Memory: https://drmemory.org/

### Linux
- Valgrind memcheck
- AddressSanitizer (ASAN): Biên dịch với `-fsanitize=address`

### Mac
- Instruments (đi kèm với Xcode)
- AddressSanitizer: Biên dịch với `-fsanitize=address`

## Ghi chú

- Một số ví dụ có chứa đoạn code được comment để tránh crash chương trình. Nếu muốn xem các lỗi thực tế, bạn có thể uncomment chúng.
- Để hiểu rõ hơn về việc cấp phát và giải phóng bộ nhớ, hãy thử chạy các ví dụ với các công cụ phân tích bộ nhớ như Valgrind.
