# Makefile cho việc xây dựng static và dynamic library
# Định nghĩa compiler và các flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Flag cho Position Independent Code (PIC)
PICFLAGS = -fPIC

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
PIC_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.pic.o,$(SRC_FILES))

# Mục tiêu mặc định
all: static dynamic main_static main_dynamic

# Tạo thư mục
directories:
	-mkdir $(OBJ_DIR) 2>NUL
	-mkdir $(LIB_DIR) 2>NUL
	-mkdir $(BIN_DIR) 2>NUL

# Biên dịch source files thành object files

# Biên dịch cho static library (không cần -fPIC)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Biên dịch cho dynamic library (cần -fPIC)
$(OBJ_DIR)/%.pic.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

# Tạo static library
static: directories $(OBJ_FILES)
	ar rcs $(STATIC_LIB) $(OBJ_FILES)
	@echo Static library created: $(STATIC_LIB)

# Tạo dynamic library
dynamic: directories $(PIC_OBJ_FILES)
	$(CC) -shared -o $(DYNAMIC_LIB) $(PIC_OBJ_FILES) $(CFLAGS)
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
