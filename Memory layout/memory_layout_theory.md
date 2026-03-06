# Bố cục bộ nhớ trong C/C++ (Memory Layout)

## Giới thiệu về bố cục bộ nhớ

Khi một chương trình C/C++ được thực thi, hệ điều hành cấp phát bộ nhớ cho nó theo một cấu trúc nhất định. Hiểu về cách bộ nhớ được tổ chức là vô cùng quan trọng để viết code hiệu quả và tránh các lỗi liên quan đến quản lý bộ nhớ như memory leak, dangling pointers, buffer overflow...

Bố cục bộ nhớ của một chương trình C/C++ khi đang chạy thường được chia thành các vùng (segment) chính sau:

```
Địa chỉ cao  +------------------------+
             |         Stack         |
             |           ↓           |
             |                       |
             |                       |
             |           ↑           |
             |         Heap          |
             +------------------------+
             |    BSS Segment        |
             +------------------------+
             |    Data Segment       |
             +------------------------+
             |    Text Segment       |
Địa chỉ thấp +------------------------+
```

## Các phân vùng bộ nhớ chính

### 1. Text Segment (Phân vùng mã lệnh)

Text segment còn được gọi là Code segment, chứa:
- Mã máy (machine code) của chương trình sau khi biên dịch
- Các hằng số (constants) có giá trị không thay đổi trong quá trình chạy chương trình

**Đặc điểm:**
- Chỉ đọc (read-only) - để ngăn chặn chương trình tự sửa đổi mã lệnh
- Có thể chia sẻ giữa nhiều tiến trình chạy cùng một chương trình
- Kích thước cố định và được xác định tại thời điểm biên dịch

### 2. Data Segment (Phân vùng dữ liệu)

Data segment chứa:
- Biến toàn cục (global variables) và biến tĩnh (static variables) có khởi tạo giá trị
- Được chia thành hai phần:
  - **Read-only data segment**: Chứa các hằng số như chuỗi ký tự hằng
  - **Read-write data segment**: Chứa các biến toàn cục và tĩnh có khởi tạo

**Đặc điểm:**
- Kích thước cố định và được xác định tại thời điểm biên dịch
- Tồn tại trong suốt thời gian chạy của chương trình

### 3. BSS Segment (Block Started by Symbol)

BSS segment chứa:
- Biến toàn cục và biến tĩnh chưa được khởi tạo (hoặc khởi tạo bằng 0)

**Đặc điểm:**
- Được hệ điều hành khởi tạo với giá trị 0 khi chương trình bắt đầu
- Tiết kiệm dung lượng file thực thi (không cần lưu trữ các giá trị 0)
- Kích thước cố định và được xác định tại thời điểm biên dịch

### 4. Heap (Vùng nhớ động)

Heap là vùng nhớ dùng cho việc cấp phát động:
- Được quản lý thông qua các hàm như `malloc()`, `calloc()`, `realloc()`, `free()` trong C
- Hoặc các toán tử `new`, `delete` trong C++

**Đặc điểm:**
- Kích thước có thể thay đổi trong quá trình chạy chương trình
- Cần quản lý thủ công (thu hồi bộ nhớ sau khi sử dụng)
- Địa chỉ tăng từ thấp đến cao
- Dễ gây ra memory leak nếu quản lý không tốt

### 5. Stack (Ngăn xếp)

Stack chứa:
- Biến cục bộ (local variables)
- Tham số hàm (function parameters)
- Địa chỉ trở về (return addresses)
- Giá trị thanh ghi được lưu khi gọi hàm

**Đặc điểm:**
- Hoạt động theo cơ chế LIFO (Last In, First Out)
- Kích thước giới hạn (thường là vài MB, tùy thuộc vào hệ điều hành)
- Quản lý bộ nhớ tự động (biến được giải phóng khi ra khỏi phạm vi)
- Địa chỉ giảm từ cao xuống thấp
- Stack overflow xảy ra khi sử dụng quá nhiều bộ nhớ stack (ví dụ: đệ quy vô hạn)

## So sánh Stack và Heap

| Tiêu chí | Stack | Heap |
|----------|-------|------|
| Quản lý bộ nhớ | Tự động | Thủ công |
| Thời gian cấp phát | Nhanh | Chậm hơn |
| Kích thước | Giới hạn | Lớn hơn, linh hoạt |
| Phân mảnh | Không | Có thể xảy ra |
| Thời gian tồn tại | Chỉ trong phạm vi | Cho đến khi thu hồi |
| Rủi ro | Stack overflow | Memory leak, dangling pointers |
