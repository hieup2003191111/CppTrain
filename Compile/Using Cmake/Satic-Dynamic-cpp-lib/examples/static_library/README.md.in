# Ví dụ về Static Library

Đây là một ví dụ đơn giản về cách tạo và sử dụng một Static Library trong C++.

## Cấu trúc thư mục

- `math_library.h`: Header file cho thư viện
- `math_library.cpp`: Implementation của thư viện
- `main.cpp`: Chương trình sử dụng thư viện
- `CMakeLists.txt`: File cấu hình CMake

## Cách build và chạy

### Bước 1: Tạo thư mục build

```bash
mkdir build
cd build
```

### Bước 2: Chạy CMake để tạo project files

```bash
cmake ..
```

### Bước 3: Build project

```bash
cmake --build .
```

Hoặc nếu sử dụng Windows:

```powershell
cmake --build . --config Release
```

### Bước 4: Chạy chương trình

```bash
./math_program
```

Hoặc nếu sử dụng Windows:

```powershell
.\Release\math_program.exe
```

## Giải thích

1. CMake sẽ tạo một static library từ file `math_library.cpp`
2. Sau đó, nó sẽ tạo một executable từ file `main.cpp` và link với static library đã tạo
3. Khi build, static library sẽ được nhúng trực tiếp vào file executable

## Kết quả mong đợi

```
Static Library Example
----------------------
10 + 5 = 15
10 - 5 = 5
10 * 5 = 50
10 / 5 = 2
```
