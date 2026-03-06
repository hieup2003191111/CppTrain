# Ví dụ về Dynamic Library

Đây là một ví dụ đơn giản về cách tạo và sử dụng một Dynamic Library trong C++.

## Cấu trúc thư mục

- `string_utils.h`: Header file cho thư viện
- `string_utils.cpp`: Implementation của thư viện
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
./string_program
```

Hoặc nếu sử dụng Windows:

```powershell
.\Release\string_program.exe
```

## Giải thích

1. CMake sẽ tạo một dynamic library từ file `string_utils.cpp`
   - Trên Windows: Tạo file `.dll` và `.lib`
   - Trên Linux: Tạo file `.so`
   - Trên macOS: Tạo file `.dylib`
2. Sau đó, nó sẽ tạo một executable từ file `main.cpp` và link với dynamic library đã tạo
3. Khi chạy, executable sẽ tải dynamic library vào bộ nhớ

## Lưu ý quan trọng

- Trên Windows, đảm bảo rằng file DLL nằm trong cùng thư mục với executable hoặc nằm trong PATH
- Trên Linux, nếu gặp lỗi "cannot open shared object file", hãy sử dụng `LD_LIBRARY_PATH`:
  ```bash
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./
  ```

## Kết quả mong đợi

```
Dynamic Library Example
----------------------
Original: Hello, World!
To Upper: HELLO, WORLD!
To Lower: hello, world!

Splitting: apple,banana,cherry,date
- apple
- banana
- cherry
- date

Joining words: "This" "is" "a" "test" 
Result: This is a test
```
