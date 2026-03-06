# Biểu diễn trực quan về bố cục bộ nhớ trong C/C++

## Sơ đồ tổng quan về bố cục bộ nhớ

```
Địa chỉ cao (0xFFFFFFFF)  +---------------------------+
                         |                           |
                         |      Vùng nhớ kernel      |  → Dành riêng cho hệ điều hành
                         |                           |
                         +---------------------------+
                         |                           |
                         |          Stack            |  → Biến cục bộ, tham số hàm
                         |         (↓↓↓↓↓)           |     Tăng từ cao xuống thấp
                         |                           |
                         +---------------------------+
                         |                           |
                         |      Memory Mapping       |  → Thư viện chia sẻ, mmap files
                         |                           |
                         +---------------------------+
                         |                           |
                         |           Heap            |  → Bộ nhớ được cấp phát động
                         |         (↑↑↑↑↑)           |     Tăng từ thấp lên cao
                         |                           |
                         +---------------------------+
                         |       BSS Segment         |  → Biến toàn cục & tĩnh chưa khởi tạo
                         +---------------------------+
                         |      Data Segment         |  → Biến toàn cục & tĩnh đã khởi tạo
                         +---------------------------+
                         |      Text Segment         |  → Mã lệnh thực thi, hằng số
Địa chỉ thấp (0x00000000) +---------------------------+
```

## Chi tiết các phân vùng bộ nhớ

### 1. Text Segment (Read-only)

```
+---------------------------+
|    Mã máy của chương      |
|    trình (machine code)   |
+---------------------------+
|     Hằng chuỗi và các     |
|       hằng số khác        |
+---------------------------+
```

**Ví dụ:**
```cpp
const int MAX_SIZE = 100;       // Lưu trong text segment
char* message = "Hello World";  // Chuỗi "Hello World" lưu trong text segment
```

### 2. Data Segment (Initialized Data)

```
+---------------------------+
|    Biến toàn cục đã       |
|     khởi tạo giá trị      |
+---------------------------+
|    Biến tĩnh (static)     |
|     đã khởi tạo           |
+---------------------------+
```

**Ví dụ:**
```cpp
int counter = 0;                // Lưu trong data segment
static double pi = 3.14159;     // Lưu trong data segment
```

### 3. BSS Segment (Uninitialized Data)

```
+---------------------------+
|    Biến toàn cục chưa     |
|       khởi tạo            |
+---------------------------+
|    Biến tĩnh (static)     |
|      chưa khởi tạo        |
+---------------------------+
```

**Ví dụ:**
```cpp
int total;                     // Lưu trong BSS segment
static char buffer[1024];      // Lưu trong BSS segment
```

### 4. Heap

```
+---------------------------+
|       Vùng nhớ trống      |
+---------------------------+
|     Đối tượng được cấp    |
|       phát động           |
+---------------------------+
|                           |
|           ↑↑↑             |
|      Hướng tăng trưởng    |
+---------------------------+
```

**Ví dụ:**
```cpp
int* dynamicInt = new int;     // Giá trị lưu trong heap
char* buffer = (char*)malloc(100); // Vùng nhớ 100 byte trong heap
```

### 5. Stack

```
+---------------------------+
|           ↓↓↓             |
|      Hướng tăng trưởng    |
+---------------------------+
|     Stack frame hiện tại  |
|    (hàm đang thực thi)    |
+---------------------------+
|   Stack frame của hàm gọi |
+---------------------------+
|     ...các frame khác     |
+---------------------------+
```

**Chi tiết stack frame:**
```
+---------------------------+
|    Tham số hàm (params)   |
+---------------------------+
|    Địa chỉ trở về (RA)    |
+---------------------------+
|     Giá trị thanh ghi     |
+---------------------------+
|      Biến cục bộ          |
+---------------------------+
```

**Ví dụ:**
```cpp
void function() {
    int localVar;           // Lưu trong stack
    double values[10];      // Mảng lưu trong stack
}
```

## Minh họa đệ quy và stack

```
+---------------------------+
| function(3): localVar     | <- Stack pointer
+---------------------------+
| function(2): localVar     |
+---------------------------+
| function(1): localVar     |
+---------------------------+
| main(): variables         |
+---------------------------+
```

## Bố cục bộ nhớ cho đối tượng

### Đối tượng trên Stack:

```cpp
class MyClass {
    int x, y;
    double value;
};

void function() {
    MyClass obj;  // Đối tượng trên stack
}
```

```
Stack:
+---------------------------+
| function():               |
|   obj.x  (4 bytes)        |
|   obj.y  (4 bytes)        |
|   obj.value (8 bytes)     |
+---------------------------+
```

### Đối tượng trên Heap:

```cpp
void function() {
    MyClass* obj = new MyClass();  // Đối tượng trên heap
}
```

```
Stack:                         Heap:
+------------------+           +------------------+
| function():      |           |  MyClass object: |
|   obj (pointer)  |---------->|    x (4 bytes)   |
+------------------+           |    y (4 bytes)   |
                               |    value (8 bytes)|
                               +------------------+
```

## Memory Padding và Alignment

Alignment đảm bảo rằng dữ liệu được lưu trữ tại địa chỉ bộ nhớ phù hợp để CPU truy cập hiệu quả.

### Không tối ưu:

```cpp
struct BadStruct {
    char c;     // 1 byte
    double d;   // 8 bytes
    int i;      // 4 bytes
};
```

```
+------------------+
| c   | <padding>  |  (1 byte + 7 bytes padding)
+------------------+
| d               |  (8 bytes)
+------------------+
| i   | <padding>  |  (4 bytes + 4 bytes padding)
+------------------+
Tổng kích thước: 24 bytes
```

### Tối ưu:

```cpp
struct GoodStruct {
    double d;   // 8 bytes
    int i;      // 4 bytes
    char c;     // 1 byte
};
```

```
+------------------+
| d               |  (8 bytes)
+------------------+
| i   | c | <pad> |  (4 bytes + 1 byte + 3 bytes padding)
+------------------+
Tổng kích thước: 16 bytes
```
