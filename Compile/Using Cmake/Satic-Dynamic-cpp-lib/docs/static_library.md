# Hướng dẫn tạo Static Library trong C/C++

## Giới thiệu

Static Library (thư viện tĩnh) là tập hợp các object file được đóng gói lại để có thể tái sử dụng trong nhiều chương trình khác nhau. Khi một chương trình sử dụng static library, mã của thư viện được nhúng trực tiếp vào trong file thực thi cuối cùng.

## Quy trình tạo Static Library

### 1. Viết mã nguồn

Đầu tiên, chúng ta cần viết mã nguồn cho thư viện của mình. Thư viện thường bao gồm:
- Header file (`.h`): Khai báo các hàm, class, struct, v.v.
- Source file (`.c`/`.cpp`): Triển khai các khai báo từ header file

### 2. Biên dịch mã nguồn thành object file

Sử dụng compiler để biên dịch các source file thành object file. Lệnh biên dịch có thể khác nhau tùy thuộc vào compiler và hệ điều hành.

#### GCC/G++ (Linux/macOS)

```bash
g++ -c -Wall -Werror -fpic my_library.cpp -o my_library.o
```

#### MSVC (Windows)

```bash
cl /c /EHsc my_library.cpp
```

### 3. Tạo Static Library từ các object file

#### GCC/G++ (Linux/macOS)

```bash
ar rcs libmy_library.a my_library.o
```

#### MSVC (Windows)

```bash
lib /OUT:my_library.lib my_library.obj
```

### 4. Sử dụng Static Library trong chương trình

#### GCC/G++ (Linux/macOS)

```bash
g++ main.cpp -L. -lmy_library -o my_program
```

#### MSVC (Windows)

```bash
cl /EHsc main.cpp my_library.lib
```

## Ví dụ thực tế

Xem ví dụ đầy đủ trong thư mục `examples/static_library`.

## Sử dụng CMake để tạo Static Library

CMake làm cho quá trình tạo thư viện dễ dàng hơn và độc lập với nền tảng. Dưới đây là một ví dụ về CMakeLists.txt để tạo static library:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

# Tạo static library
add_library(my_library STATIC
    src/my_library.cpp
)

# Thiết lập thư mục include
target_include_directories(my_library PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tạo một executable sử dụng thư viện
add_executable(my_program
    src/main.cpp
)

# Link thư viện với executable
target_link_libraries(my_program
    my_library
)
```

## Ưu và nhược điểm của Static Library

### Ưu điểm

1. **Không phụ thuộc vào thư viện bên ngoài**: Chương trình có thể chạy mà không cần các file thư viện riêng biệt
2. **Hiệu suất tốt**: Không tốn thời gian để tải thư viện khi chạy
3. **Không có vấn đề về phiên bản**: Không lo lắng về việc xung đột phiên bản thư viện

### Nhược điểm

1. **Kích thước file thực thi lớn**: Mã của thư viện được sao chép vào mọi file thực thi sử dụng nó
2. **Cần biên dịch lại khi thư viện thay đổi**: Nếu thư viện được cập nhật, tất cả các chương trình sử dụng nó cũng cần được biên dịch lại
3. **Lãng phí bộ nhớ**: Nếu nhiều chương trình sử dụng cùng một thư viện, mỗi chương trình sẽ có một bản sao riêng trong bộ nhớ

## Lưu ý quan trọng

- Đặt tên thư viện theo quy ước: Trên Linux/macOS, thư viện tĩnh thường có tên bắt đầu bằng `lib` và kết thúc bằng `.a` (ví dụ: `libmy_library.a`)
- Header file nên được thiết kế cẩn thận, chỉ expose những API cần thiết
- Nên sử dụng header guards hoặc `#pragma once` để tránh include nhiều lần
- Xem xét sử dụng namespace để tránh xung đột tên

## Tham khảo thêm

- [GNU ar documentation](https://www.gnu.org/software/binutils/manual/binutils.html)
- [MSVC lib documentation](https://docs.microsoft.com/en-us/cpp/build/reference/lib-reference)
