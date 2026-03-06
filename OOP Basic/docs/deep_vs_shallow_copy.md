# OOP Deep Copy và Shallow Copy trong C++

## 1. Khái niệm

### Shallow Copy (Sao chép nông)
- Là quá trình sao chép các giá trị của các thành viên dữ liệu từ đối tượng này sang đối tượng khác.
- Nếu đối tượng có con trỏ hoặc tài nguyên động, cả hai đối tượng sẽ trỏ đến cùng một vùng nhớ.
- Dễ gây lỗi double free hoặc dữ liệu bị thay đổi ngoài ý muốn.

### Deep Copy (Sao chép sâu)
- Là quá trình sao chép toàn bộ dữ liệu, bao gồm cả vùng nhớ động mà đối tượng quản lý.
- Mỗi đối tượng sẽ có vùng nhớ riêng biệt.
- An toàn hơn khi làm việc với con trỏ hoặc tài nguyên động.

## 2. Khi nào cần dùng?
- Nếu lớp có con trỏ hoặc quản lý tài nguyên động (heap), nên dùng Deep Copy.
- Nếu chỉ chứa dữ liệu cơ bản (int, float, char, ...), Shallow Copy là đủ.

## 3. Cách cài đặt
- C++ mặc định sử dụng Shallow Copy khi dùng copy constructor hoặc phép gán (=).
- Để Deep Copy, cần tự định nghĩa copy constructor và operator=.

## 4. Ví dụ minh họa
Xem file `sample_deep_shallow.cpp` trong thư mục này.

---
