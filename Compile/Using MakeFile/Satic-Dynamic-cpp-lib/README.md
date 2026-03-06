# Hướng dẫn xây dựng Static Library và Dynamic Library trong C/C++ sử dụng Makefile

## 1. Giới thiệu
- **Static Library (Thư viện tĩnh)**: Được liên kết vào chương trình tại thời điểm biên dịch, file thường có đuôi `.a` (Linux) hoặc `.lib` (Windows).
  - Ưu điểm: Chương trình hoàn toàn độc lập, không cần file thư viện riêng lẻ khi chạy
  - Nhược điểm: Kích thước file thực thi lớn, nhiều ứng dụng sử dụng cùng thư viện sẽ có nhiều bản sao
- **Dynamic Library (Thư viện động)**: Được liên kết tại thời điểm chạy, file thường có đuôi `.so` (Linux) hoặc `.dll` (Windows).
  - Ưu điểm: Kích thước file thực thi nhỏ, nhiều ứng dụng có thể dùng chung một thư viện
  - Nhược điểm: Cần phải có file thư viện để chương trình chạy được

## 2. Cấu trúc thư mục dự án
```
Satic-Dynamic-cpp-lib/
├── include/        # Chứa các file header
│   └── mylib.h     # File header của thư viện
├── src/           # Chứa các file mã nguồn
│   └── mylib.c    # File mã nguồn của thư viện
├── obj/           # Thư mục chứa các file object (.o) - sẽ được tạo bởi Makefile
├── lib/           # Thư mục chứa các thư viện - sẽ được tạo bởi Makefile
│   ├── libmylib.a # Static library
│   └── mylib.dll  # Dynamic library
├── bin/           # Thư mục chứa các file thực thi - sẽ được tạo bởi Makefile
│   ├── main_static.exe  # Chương trình dùng static library
│   └── main_dynamic.exe # Chương trình dùng dynamic library
├── main.c         # File mã nguồn chính để test thư viện
├── Makefile       # Makefile để tự động hóa quá trình build
└── README.md      # File hướng dẫn này
```

## 3. Ví dụ mã nguồn
### `include/mylib.h`
```c
#ifndef MYLIB_H
#define MYLIB_H

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define MYLIB_API __declspec(dllexport)
    #else
        #define MYLIB_API __declspec(dllimport)
    #endif
#else
    #define MYLIB_API
#endif

/**
 * @brief In một thông báo chào mừng
 */
MYLIB_API void hello();

/**
 * @brief Tính tổng hai số nguyên
 * 
 * @param a Số nguyên thứ nhất
 * @param b Số nguyên thứ hai
 * @return Tổng của hai số
 */
MYLIB_API int add(int a, int b);

/**
 * @brief Tính hiệu hai số nguyên
 * 
 * @param a Số nguyên thứ nhất
 * @param b Số nguyên thứ hai
 * @return Hiệu của hai số
 */
MYLIB_API int subtract(int a, int b);

#endif /* MYLIB_H */
```

### `src/mylib.c`
```c
#include <stdio.h>
#include "../include/mylib.h"

#ifdef _WIN32
    #define BUILDING_DLL
#endif

void hello() {
    printf("Hello from library!\n");
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
```

### `main.c`
```c
#include <stdio.h>
#include "include/mylib.h"

int main() {
    hello();
    
    int result1 = add(10, 5);
    int result2 = subtract(10, 5);
    
    printf("10 + 5 = %d\n", result1);
    printf("10 - 5 = %d\n", result2);
    
    return 0;
}
```

## 4. Makefile đầy đủ
```makefile
# Makefile cho việc xây dựng static và dynamic library
# Định nghĩa compiler và các flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Đường dẫn
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

# Tạo các thư mục nếu chưa tồn tại
$(shell if not exist $(OBJ_DIR) mkdir $(OBJ_DIR))
$(shell if not exist $(LIB_DIR) mkdir $(LIB_DIR))
$(shell if not exist $(BIN_DIR) mkdir $(BIN_DIR))

# Tên thư viện
LIB_NAME = mylib
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
DYNAMIC_LIB = $(LIB_DIR)/$(LIB_NAME).dll

# Source và object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Mục tiêu mặc định
all: static dynamic main_static main_dynamic

# Tạo thư mục
directories:
	-mkdir $(OBJ_DIR) 2>NUL
	-mkdir $(LIB_DIR) 2>NUL
	-mkdir $(BIN_DIR) 2>NUL

# Biên dịch source files thành object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Tạo static library
static: directories $(OBJ_FILES)
	ar rcs $(STATIC_LIB) $(OBJ_FILES)
	@echo Static library created: $(STATIC_LIB)

# Tạo dynamic library
dynamic: directories $(SRC_FILES)
	$(CC) -shared -o $(DYNAMIC_LIB) $(SRC_FILES) $(CFLAGS)
	@echo Dynamic library created: $(DYNAMIC_LIB)

# Biên dịch chương trình chính với static library
main_static: static
	$(CC) main.c -L$(LIB_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/main_static.exe $(CFLAGS)
	@echo Static executable created: $(BIN_DIR)/main_static.exe

# Biên dịch chương trình chính với dynamic library
main_dynamic: dynamic
	$(CC) main.c -L$(LIB_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/main_dynamic.exe $(CFLAGS)
	@echo Dynamic executable created: $(BIN_DIR)/main_dynamic.exe
	@echo Note: Make sure $(LIB_DIR) is in your PATH or copy $(DYNAMIC_LIB) to the same directory as the executable

# Làm sạch
clean:
	-del /Q $(OBJ_DIR)\*.o 2>NUL
	-del /Q $(LIB_DIR)\*.a 2>NUL
	-del /Q $(LIB_DIR)\*.dll 2>NUL
	-del /Q $(BIN_DIR)\*.exe 2>NUL

.PHONY: all clean static dynamic main_static main_dynamic directories
```

## 5. Giải thích các thành phần trong Makefile
- `CC`: Định nghĩa compiler được sử dụng (gcc)
- `CFLAGS`: Các flag cho compiler, bao gồm:
  - `-Wall -Wextra`: Hiển thị tất cả cảnh báo
  - `-g`: Thêm thông tin debug
  - `-Iinclude`: Thêm thư mục include vào đường dẫn tìm kiếm
- `$(shell ...)`: Thực thi lệnh shell để tạo thư mục nếu chưa tồn tại
- `$(wildcard ...)`: Tìm tất cả file theo mẫu
- `$(patsubst ...)`: Thay thế mẫu trong chuỗi
- `ar rcs`: Lệnh để tạo static library (r: thêm vào, c: tạo mới, s: tạo index)
- `-shared`: Flag để tạo dynamic library (DLL)
- `-L$(LIB_DIR)`: Chỉ định thư mục chứa thư viện
- `-l$(LIB_NAME)`: Liên kết với thư viện

## 6. Hướng dẫn sử dụng
1. Đảm bảo bạn đã có môi trường phát triển C/C++ (ví dụ: MinGW trên Windows hoặc GCC trên Linux)
2. Mở terminal trong thư mục dự án
3. Chạy các lệnh sau:

```bash
# Tạo tất cả (static + dynamic library và chương trình)
make all

# Hoặc tạo từng phần riêng biệt:
# Chỉ tạo static library
make static

# Chỉ tạo dynamic library
make dynamic

# Tạo chương trình sử dụng static library
make main_static

# Tạo chương trình sử dụng dynamic library
make main_dynamic

# Chạy chương trình sử dụng static library
bin\main_static.exe

# Chạy chương trình sử dụng dynamic library 
# (đảm bảo mylib.dll có thể được tìm thấy)
bin\main_dynamic.exe

# Dọn dẹp các file tạm
make clean
```

## 7. Lưu ý quan trọng
### Static Library
- Trên Windows, thư viện tĩnh thường có đuôi `.lib`, nhưng khi sử dụng GCC/MinGW vẫn sử dụng đuôi `.a`
- Khi biên dịch với static library, tất cả code của thư viện sẽ được đưa vào file thực thi
- File thực thi sử dụng static library không cần file thư viện khi chạy

### Dynamic Library
- Trên Windows, thư viện động là `.dll`, trên Linux là `.so`
- Đảm bảo đường dẫn thư viện động nằm trong PATH hoặc cùng thư mục với file thực thi khi chạy chương trình
- Trên Windows, có thể cần copy file DLL vào thư mục chứa file EXE hoặc thêm thư mục lib vào biến PATH

### Để thêm thư mục vào PATH tạm thời (Windows)
```powershell
$env:PATH += ";C:\đường\dẫn\đến\thư\mục\lib"
```

## 8. Các lỗi thường gặp
1. **Lỗi "library not found"**: Đảm bảo tên thư viện trong lệnh biên dịch đúng với tên thư viện đã tạo
2. **Lỗi "undefined reference"**: Đảm bảo hàm được khai báo trong header và được định nghĩa trong file nguồn
3. **Lỗi "DLL not found"**: Đảm bảo file DLL nằm trong PATH hoặc cùng thư mục với file thực thi

## 9. Mở rộng
- Thêm các target để cài đặt thư viện vào hệ thống
- Tối ưu hóa flags biên dịch cho môi trường production
- Thêm các test case tự động

---
Bạn có thể chỉnh sửa Makefile và mã nguồn cho phù hợp với dự án thực tế của mình.
