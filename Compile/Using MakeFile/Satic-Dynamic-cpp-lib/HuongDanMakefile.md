# Makefile - Công cụ tự động hóa quá trình biên dịch

## I. Giới thiệu về Makefile

### Makefile là gì?

Makefile là một tập tin chứa các quy tắc (rules) để tự động hóa quá trình biên dịch và xây dựng phần mềm. Makefile được sử dụng bởi công cụ `make` - một tiện ích dòng lệnh có mặt trên hầu hết các hệ điều hành.

### Lợi ích của Makefile

1. **Tự động hóa:** Tự động hóa quá trình biên dịch phức tạp với nhiều bước
2. **Biên dịch chọn lọc:** Chỉ biên dịch lại các file đã thay đổi, tiết kiệm thời gian
3. **Tái sử dụng:** Định nghĩa quy trình xây dựng một lần, sử dụng nhiều lần
4. **Quản lý phụ thuộc:** Quản lý mối quan hệ phụ thuộc giữa các file nguồn
5. **Hỗ trợ nhiều mục tiêu:** Cho phép tạo nhiều mục tiêu (targets) khác nhau từ cùng mã nguồn

## II. Cú pháp cơ bản của Makefile

### Quy tắc (Rule)

Cấu trúc cơ bản của một quy tắc trong Makefile:

```makefile
target: dependencies
    commands
```

Trong đó:
- **target:** Tên của mục tiêu (thường là tên file cần tạo ra)
- **dependencies:** Danh sách các file phụ thuộc (file cần có trước khi tạo target)
- **commands:** Các lệnh cần chạy để tạo ra target (phải bắt đầu bằng TAB, không phải dấu cách)

### Ví dụ đơn giản

```makefile
hello: hello.c
    gcc -o hello hello.c
```

Khi chạy `make hello`, công cụ make sẽ kiểm tra:
1. File `hello` có tồn tại không?
2. Nếu không tồn tại hoặc cũ hơn `hello.c`, sẽ chạy lệnh `gcc -o hello hello.c`

### Biến (Variables)

Định nghĩa và sử dụng biến trong Makefile:

```makefile
CC = gcc
CFLAGS = -Wall -g

hello: hello.c
    $(CC) $(CFLAGS) -o hello hello.c
```

### Các biến đặc biệt

- `$@`: Tên của target
- `$<`: Phần tử đầu tiên trong danh sách dependencies
- `$^`: Toàn bộ danh sách dependencies
- `$*`: Phần tên file (không có extension) của target

```makefile
hello: hello.c helper.c
    gcc -o $@ $^
```

## III. Quy tắc ngầm định (Implicit Rules)

Make có nhiều quy tắc ngầm định giúp rút gọn Makefile:

```makefile
CC = gcc
CFLAGS = -Wall -g

hello: hello.o helper.o
    $(CC) -o $@ $^

# Quy tắc ngầm định: %.o: %.c
#     $(CC) $(CFLAGS) -c $< -o $@
```

## IV. Phụ thuộc tự động (Automatic Dependencies)

### Tạo file phụ thuộc với GCC

```makefile
CC = gcc
CFLAGS = -Wall -g
DEPFLAGS = -MMD -MP
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: program

program: $(OBJS)
    $(CC) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPS)
```

## V. Hàm (Functions) trong Makefile

### Một số hàm phổ biến:

- `wildcard`: Tìm file theo mẫu
- `patsubst`: Thay thế mẫu trong chuỗi
- `notdir`: Lấy tên file từ đường dẫn
- `addprefix`: Thêm tiền tố
- `addsuffix`: Thêm hậu tố
- `shell`: Thực thi lệnh shell

```makefile
# Tìm tất cả file .c trong thư mục hiện tại
SRCS = $(wildcard *.c)
# Chuyển đổi từ .c sang .o
OBJS = $(patsubst %.c,%.o,$(SRCS))
# Thêm đường dẫn obj/ vào trước tên file
OBJ_FILES = $(addprefix obj/,$(OBJS))
```

## VI. Mục tiêu đặc biệt (Special Targets)

### 1. `.PHONY`

Định nghĩa các mục tiêu không phải là file:

```makefile
.PHONY: all clean

all: program

program: main.o
    gcc -o program main.o

clean:
    rm -f program *.o
```

### 2. `.DEFAULT_GOAL`

Chỉ định mục tiêu mặc định khi gọi `make` không có tham số:

```makefile
.DEFAULT_GOAL := all

all: program
```

## VII. Makefile cho dự án C/C++ lớn

### Cấu trúc thư mục

```
project/
├── include/
├── src/
├── obj/
├── bin/
└── Makefile
```

### Makefile

```makefile
# Compiler và flags
CC = gcc
CXX = g++
CFLAGS = -Wall -Iinclude
CXXFLAGS = -Wall -Iinclude

# Đường dẫn
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Tìm tất cả file nguồn
C_SRCS = $(wildcard $(SRC_DIR)/*.c)
CXX_SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Chuyển đổi từ .c/.cpp sang .o
C_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
CXX_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CXX_SRCS))

# Tất cả các object files
OBJS = $(C_OBJS) $(CXX_OBJS)

# Tên chương trình
TARGET = $(BIN_DIR)/program

# Mục tiêu mặc định
all: $(TARGET)

# Tạo thư mục nếu chưa tồn tại
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Biên dịch file .c thành .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Biên dịch file .cpp thành .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Liên kết thành chương trình
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) -o $@ $^

# Làm sạch
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
```

## VIII. Makefile cho thư viện

### Thư viện tĩnh (Static Library)

```makefile
# Compiler và flags
CC = gcc
CFLAGS = -Wall -fPIC -Iinclude

# Đường dẫn
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

# Tên thư viện
LIB_NAME = mylib
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a

# Các file nguồn và object
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Tạo thư viện tĩnh
static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS) | $(LIB_DIR)
	ar rcs $@ $^

# Biên dịch .c thành .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tạo thư mục
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Làm sạch
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

.PHONY: static clean
```

### Thư viện động (Dynamic Library)

```makefile
# Compiler và flags
CC = gcc
CFLAGS = -Wall -fPIC -Iinclude

# Đường dẫn
SRC_DIR = src
LIB_DIR = lib

# Tên thư viện
LIB_NAME = mylib
DYNAMIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).so

# Các file nguồn
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Tạo thư viện động
dynamic: $(DYNAMIC_LIB)

$(DYNAMIC_LIB): $(SRCS) | $(LIB_DIR)
	$(CC) -shared $(CFLAGS) -o $@ $^

# Tạo thư mục
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Làm sạch
clean:
	rm -rf $(LIB_DIR)

.PHONY: dynamic clean
```

## IX. Điều kiện trong Makefile

### Cú pháp điều kiện

```makefile
ifeq ($(OS),Windows_NT)
    # Lệnh cho Windows
    CLEAN_CMD = del /Q
else
    # Lệnh cho Unix/Linux
    CLEAN_CMD = rm -f
endif

clean:
	$(CLEAN_CMD) *.o
```

### Kiểm tra biến có được định nghĩa

```makefile
ifdef DEBUG
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -O2
endif
```

## X. Các kỹ thuật nâng cao

### Bao gồm file khác

```makefile
include config.mk
include rules/*.mk
```

### Tạo Makefile đa nền tảng

```makefile
# Phát hiện OS
ifeq ($(OS),Windows_NT)
    OS_TYPE := Windows
    EXE_EXT := .exe
    OBJ_EXT := .obj
    LIB_PREFIX :=
    LIB_EXT := .lib
    SHARED_EXT := .dll
    RM := del /Q
    MKDIR := mkdir
else
    OS_TYPE := $(shell uname -s)
    EXE_EXT :=
    OBJ_EXT := .o
    LIB_PREFIX := lib
    ifeq ($(OS_TYPE),Darwin)
        LIB_EXT := .a
        SHARED_EXT := .dylib
    else
        LIB_EXT := .a
        SHARED_EXT := .so
    endif
    RM := rm -f
    MKDIR := mkdir -p
endif

# Sử dụng các biến
TARGET = program$(EXE_EXT)
STATIC_LIB = $(LIB_PREFIX)mylib$(LIB_EXT)
SHARED_LIB = $(LIB_PREFIX)mylib$(SHARED_EXT)
```

### Tạo Makefile song song (Parallel)

```makefile
.PHONY: all
all: program1 program2 program3

# Sử dụng make -j4 để chạy song song 4 quy trình
```

## XI. Mẹo và thủ thuật

### 1. Hiển thị thông báo

```makefile
all:
	@echo "Building project..."
	gcc -o program main.c
	@echo "Build successful!"
```

### 2. Chạy lệnh shell và lưu kết quả

```makefile
VERSION := $(shell git describe --tags)
OBJS := $(shell find src -name '*.c' | sed 's/\.c/.o/g')
```

### 3. Tạo danh sách các file một cách thông minh

```makefile
# Liệt kê tất cả thư mục con
SUBDIRS := $(wildcard */.)
# Tìm tất cả .c trong các thư mục con
SRCS := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)*.c))
```

### 4. Điều hướng đầu ra lỗi

```makefile
compile:
	-gcc -o program main.c 2>errors.log || echo "Compilation failed"
```

### 5. Chạy với quyền admin

```makefile
install:
	@if [ `id -u` -ne 0 ]; then \
		echo "Please run as root"; \
		exit 1; \
	fi
	cp program /usr/local/bin/
```

## XII. Lỗi thường gặp và cách khắc phục

### 1. "Missing separator"

Lỗi: `Makefile:3: *** missing separator. Stop.`

Nguyên nhân: Sử dụng dấu cách thay vì tab để bắt đầu lệnh.

Khắc phục: Đảm bảo sử dụng tab (không phải dấu cách) ở đầu mỗi lệnh.

### 2. "No rule to make target"

Lỗi: `make: *** No rule to make target 'file.o', needed by 'program'. Stop.`

Nguyên nhân: Không tìm thấy quy tắc để tạo file.o từ file.c.

Khắc phục: Thêm quy tắc chuyển đổi hoặc kiểm tra lại tên file.

### 3. "No such file or directory"

Lỗi: `gcc: error: file.c: No such file or directory`

Nguyên nhân: File nguồn không tồn tại hoặc đường dẫn không chính xác.

Khắc phục: Kiểm tra lại đường dẫn và tên file.

## XIII. Tài liệu tham khảo

1. [GNU Make Manual](https://www.gnu.org/software/make/manual/)
2. [Managing Projects with GNU Make](http://oreilly.com/catalog/make3/book/index.csp)
3. [Makefile Tutorial](https://makefiletutorial.com/)

## XIV. Kết luận

Makefile là một công cụ mạnh mẽ giúp tự động hóa quá trình biên dịch và xây dựng phần mềm. Với kiến thức về Makefile, bạn có thể quản lý các dự án phức tạp một cách hiệu quả, tiết kiệm thời gian và giảm lỗi trong quá trình phát triển phần mềm. Mặc dù có thể có một chút khó khăn khi bắt đầu, nhưng khi đã quen thuộc, Makefile sẽ trở thành một công cụ không thể thiếu trong quy trình phát triển của bạn.
