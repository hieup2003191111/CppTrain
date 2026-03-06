# THƯ VIỆN TĨNH VÀ ĐỘNG TRONG C/C++
## Giảng dạy với Makefile

---

## Nội dung khóa học
1. **Giới thiệu về thư viện trong C/C++**
2. **Thư viện tĩnh (Static Library)**
3. **Thư viện động (Dynamic Library)**
4. **Sử dụng Makefile để xây dựng thư viện**
5. **Bài tập thực hành**
6. **Các vấn đề thường gặp và cách khắc phục**

---

## 1. Giới thiệu về thư viện trong C/C++
### 1.1. Khái niệm cơ bản
- **Thư viện là gì?** Tập hợp các hàm được viết sẵn, có thể tái sử dụng trong nhiều chương trình
- **Vai trò của thư viện**:
  * Tái sử dụng mã nguồn
  * Phân chia module trong phát triển phần mềm
  * Đơn giản hóa việc phát triển ứng dụng phức tạp

### 1.2. Phân loại thư viện
- **Thư viện tiêu chuẩn**: Đi kèm với trình biên dịch (stdio.h, stdlib.h, etc.)
- **Thư viện bên thứ ba**: Do bên thứ ba phát triển (Qt, Boost, etc.)
- **Thư viện tự phát triển**: Do lập trình viên tự phát triển

---

## 2. Thư viện tĩnh (Static Library)
### 2.1. Khái niệm
- **Static Library**: Tập hợp các đoạn mã đã biên dịch được liên kết trực tiếp vào chương trình thực thi
- **Đuôi file**: `.a` (Linux/MinGW) hoặc `.lib` (Windows/MSVC)

### 2.2. Cách thức hoạt động
- Trình biên dịch sao chép mã máy của thư viện trực tiếp vào file thực thi
- Không cần có file thư viện riêng khi chạy chương trình

### 2.3. Ưu điểm và nhược điểm
**Ưu điểm**:
- Chương trình hoàn toàn độc lập, không cần file thư viện riêng khi chạy
- Không xảy ra vấn đề phiên bản thư viện không tương thích
- Thực thi nhanh hơn (không tốn thời gian load thư viện)

**Nhược điểm**:
- Kích thước file thực thi lớn
- Nhiều ứng dụng sử dụng cùng một thư viện sẽ có nhiều bản sao
- Khi cập nhật thư viện, cần biên dịch lại toàn bộ chương trình

---

## 3. Thư viện động (Dynamic Library)
### 3.1. Khái niệm
- **Dynamic Library**: Thư viện được nạp vào bộ nhớ khi chương trình chạy
- **Đuôi file**: `.so` (Linux) hoặc `.dll` (Windows)

### 3.2. Cách thức hoạt động
- Chương trình chỉ lưu tham chiếu đến thư viện
- Hệ điều hành nạp thư viện vào bộ nhớ khi chạy chương trình
- Nhiều chương trình có thể sử dụng cùng một thư viện đã được nạp

### 3.3. Ưu điểm và nhược điểm
**Ưu điểm**:
- Kích thước file thực thi nhỏ
- Nhiều ứng dụng có thể dùng chung một thư viện (tiết kiệm bộ nhớ)
- Có thể cập nhật thư viện mà không cần biên dịch lại chương trình

**Nhược điểm**:
- Cần phải có file thư viện để chương trình chạy được
- Có thể gặp vấn đề về phiên bản thư viện không tương thích
- Chạy chậm hơn một chút do phải nạp thư viện

---

## 4. Cấu trúc dự án thư viện
### 4.1. Phân chia thư mục
```
project/
├── include/      # Header files (.h)
├── src/          # Source files (.c/.cpp)
├── obj/          # Object files (.o)
├── lib/          # Library files (.a/.dll)
├── bin/          # Executable files
├── main.c        # Test application
└── Makefile
```

### 4.2. File header (.h)
- Khai báo các hàm, cấu trúc dữ liệu, lớp...
- Sử dụng macro để hỗ trợ export/import trong thư viện động

### 4.3. File nguồn (.c/.cpp)
- Triển khai các hàm đã khai báo trong header
- Định nghĩa các hằng số, biến toàn cục...

---

## 5. Xây dựng thư viện tĩnh
### 5.1. Quy trình xây dựng
1. Biên dịch mã nguồn thành file object (.o)
2. Gom các file object thành thư viện tĩnh (.a/.lib)

### 5.2. Các lệnh tạo thư viện tĩnh
**Linux/MinGW**:
```bash
# Biên dịch file object
gcc -c -o mylib.o mylib.c

# Tạo thư viện tĩnh
ar rcs libmylib.a mylib.o
```

**Windows/MSVC**:
```bash
# Biên dịch file object
cl /c mylib.c

# Tạo thư viện tĩnh
lib /OUT:mylib.lib mylib.obj
```

---

## 6. Xây dựng thư viện động
### 6.1. Quy trình xây dựng
1. Biên dịch mã nguồn với flag position-independent code
2. Tạo thư viện động từ các file object

### 6.2. Các lệnh tạo thư viện động
**Linux**:
```bash
# Tạo thư viện động
gcc -shared -fPIC -o libmylib.so mylib.c
```

**Windows/MinGW**:
```bash
# Tạo thư viện động
gcc -shared -o mylib.dll mylib.c -Wl,--out-implib,libmylib.a
```

---

## 7. Sử dụng thư viện
### 7.1. Sử dụng thư viện tĩnh
```bash
# Linux/MinGW
gcc main.c -L. -lmylib -o main_static

# Windows/MSVC
cl main.c mylib.lib /Fe:main_static.exe
```

### 7.2. Sử dụng thư viện động
```bash
# Linux
gcc main.c -L. -lmylib -o main_dynamic

# Windows/MinGW
gcc main.c -L. -lmylib -o main_dynamic.exe
```

### 7.3. Chạy chương trình với thư viện động
**Linux**:
```bash
# Thêm thư mục chứa .so vào LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./main_dynamic
```

**Windows**:
```powershell
# Đảm bảo .dll ở cùng thư mục hoặc trong PATH
$env:PATH += ";C:\đường\dẫn\đến\thư\mục\lib"
.\main_dynamic.exe
```

---

## 8. Makefile
### 8.1. Khái niệm
- **Makefile**: Tập tin chứa các quy tắc để tự động hóa quy trình biên dịch
- **Cú pháp cơ bản**:
  ```makefile
  target: dependencies
      commands
  ```

### 8.2. Các biến trong Makefile
```makefile
CC = gcc                 # Compiler
CFLAGS = -Wall -g        # Compiler flags
SRC_DIR = src            # Source directory
OBJ_DIR = obj            # Object directory
```

### 8.3. Các hàm trong Makefile
```makefile
# Tìm tất cả file .c trong thư mục src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Chuyển đổi đường dẫn từ .c sang .o
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
```

---

## 9. Makefile cho thư viện
### 9.1. Cấu trúc Makefile
```makefile
# Các biến và đường dẫn
CC = gcc
CFLAGS = -Wall -g -Iinclude
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
```

### 9.2. Quy tắc tạo thư viện tĩnh
```makefile
# Tạo static library
static: $(OBJ_FILES)
	ar rcs $(STATIC_LIB) $(OBJ_FILES)
```

### 9.3. Quy tắc tạo thư viện động
```makefile
# Tạo dynamic library
dynamic: $(SRC_FILES)
	$(CC) -shared -o $(DYNAMIC_LIB) $(SRC_FILES) $(CFLAGS)
```

---

## 10. Thực hành
### 10.1. Tạo dự án thư viện đơn giản
1. Tạo cấu trúc thư mục
2. Tạo file header và nguồn
3. Viết Makefile
4. Build thư viện tĩnh và động
5. Kiểm tra thư viện với chương trình test

### 10.2. Chương trình mẫu
**mylib.h**
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

MYLIB_API void hello();
MYLIB_API int add(int a, int b);
MYLIB_API int subtract(int a, int b);

#endif
```

---

## 10. Thực hành (tiếp)
**mylib.c**
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

**main.c**
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

---

## 11. Các vấn đề thường gặp
### 11.1. Lỗi không tìm thấy thư viện
- **Nguyên nhân**: Đường dẫn không đúng, tên thư viện không đúng
- **Giải pháp**: Kiểm tra flag `-L` và `-l` trong lệnh biên dịch

### 11.2. Lỗi undefined reference
- **Nguyên nhân**: Hàm được khai báo nhưng không được định nghĩa
- **Giải pháp**: Kiểm tra định nghĩa hàm trong file nguồn

### 11.3. Lỗi không tìm thấy DLL
- **Nguyên nhân**: DLL không nằm trong PATH hoặc thư mục chạy chương trình
- **Giải pháp**: Đặt DLL vào thư mục chương trình hoặc thêm thư mục vào PATH

---

## 12. Bài tập thực hành
### Bài tập 1: Tạo thư viện tính toán
Tạo một thư viện có các hàm tính toán cơ bản: cộng, trừ, nhân, chia, căn bậc hai, lũy thừa.

### Bài tập 2: Tạo thư viện xử lý chuỗi
Tạo một thư viện với các hàm xử lý chuỗi: đảo chuỗi, chuyển chữ hoa/chữ thường, tìm kiếm chuỗi con.

### Bài tập 3: Tạo thư viện xử lý mảng
Tạo một thư viện với các hàm sắp xếp, tìm kiếm, tính toán thống kê trên mảng.

---

## 13. Tài liệu tham khảo
1. "The C Programming Language" - Brian W. Kernighan, Dennis M. Ritchie
2. "Managing Projects with GNU Make" - Robert Mecklenburg
3. "Advanced C and C++ Compiling" - Milan Stevanovic
4. [GNU Make Manual](https://www.gnu.org/software/make/manual/)
5. [GCC Documentation](https://gcc.gnu.org/onlinedocs/)

---

## Phụ lục: Makefile đầy đủ
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
