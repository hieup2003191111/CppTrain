# Hướng dẫn chi tiết cách dùng sample_deep_shallow.cpp

## 1. Mục đích
File này giúp bạn hiểu sự khác biệt giữa Shallow Copy và Deep Copy trong C++ khi làm việc với con trỏ.

## 2. Cách chạy
1. Mở terminal tại thư mục chứa file `sample_deep_shallow.cpp`.
2. Biên dịch file:
   ```sh
   g++ sample_deep_shallow.cpp -o sample_deep_shallow.exe
   ```
3. Chạy chương trình:
   ```sh
   ./sample_deep_shallow.exe
   ```

## 3. Giải thích kết quả
### Phần 1: Shallow Copy
- Tạo đối tượng `s1` với chuỗi "Hello".
- Tạo đối tượng `s2 = s1` (shallow copy): cả hai cùng trỏ tới cùng một vùng nhớ.
- Khi thay đổi `s2.data` thành "World", `s1.data` cũng bị thay đổi theo.
- Khi kết thúc chương trình, cả hai destructor sẽ cùng giải phóng một vùng nhớ => dễ gây lỗi double free.

### Phần 2: Deep Copy
- Tạo đối tượng `d1` với chuỗi "Hello".
- Tạo đối tượng `d2 = d1` (deep copy): mỗi đối tượng có vùng nhớ riêng.
- Khi thay đổi `d2.data` thành "World", `d1.data` không bị ảnh hưởng.
- Khi kết thúc chương trình, mỗi destructor giải phóng vùng nhớ riêng, không bị lỗi.

## 4. Kết luận
- **Shallow copy** chỉ an toàn với dữ liệu cơ bản, không dùng cho con trỏ.
- **Deep copy** cần thiết khi lớp có con trỏ hoặc quản lý tài nguyên động.

Nếu cần giải thích chi tiết từng dòng code, hãy hỏi thêm nhé!
