# Tổng quan về Static và Dynamic Library trong C/C++

## Giới thiệu

Thư viện (library) trong C/C++ là một tập hợp các hàm và dữ liệu được đóng gói để tái sử dụng. Có hai loại thư viện chính: Static Library và Dynamic Library. Tài liệu này cung cấp tổng quan về cả hai loại.

## Static Library

### Khái niệm cơ bản

Static Library (thư viện tĩnh) là một tập hợp các mã object được liên kết vào chương trình thực thi cuối cùng trong quá trình liên kết (linking). Mã của thư viện trở thành một phần không thể tách rời của file thực thi.

### Đặc điểm

- **File extension**: `.a` trên Unix/Linux, `.lib` trên Windows
- **Kích thước file thực thi**: Lớn hơn vì chứa mã của thư viện
- **Thời gian tải**: Nhanh hơn vì không cần tải thư viện riêng biệt khi chạy
- **Cập nhật**: Yêu cầu biên dịch lại toàn bộ chương trình khi thư viện thay đổi
- **Phân phối**: Đơn giản hơn vì không phụ thuộc vào thư viện bên ngoài

### Ưu điểm

- Không có dependency runtime
- Tải nhanh hơn khi chạy
- Đơn giản khi phân phối

### Nhược điểm

- File thực thi lớn hơn
- Phải biên dịch lại toàn bộ khi thư viện thay đổi
- Nhiều ứng dụng sử dụng cùng một thư viện dẫn đến lãng phí bộ nhớ

## Dynamic Library

### Khái niệm cơ bản

Dynamic Library (thư viện động) được tải vào bộ nhớ khi chương trình cần chúng, thường là khi chương trình bắt đầu chạy (nhưng cũng có thể là trong quá trình chạy). Mã của thư viện không được nhúng trong file thực thi.

### Đặc điểm

- **File extension**: `.so` trên Unix/Linux, `.dll` trên Windows, `.dylib` trên macOS
- **Kích thước file thực thi**: Nhỏ hơn vì không chứa mã thư viện
- **Thời gian tải**: Chậm hơn do phải tải thư viện khi chạy
- **Cập nhật**: Có thể cập nhật thư viện mà không cần biên dịch lại chương trình
- **Phân phối**: Phức tạp hơn vì phải đảm bảo thư viện có sẵn khi chạy

### Ưu điểm

- File thực thi nhỏ hơn
- Có thể cập nhật thư viện độc lập
- Tiết kiệm bộ nhớ khi nhiều ứng dụng sử dụng cùng một thư viện
- Hỗ trợ hot patching (cập nhật mà không cần khởi động lại)

### Nhược điểm

- DLL Hell/dependency hell (xung đột phiên bản)
- Chậm hơn do phải tải khi chạy
- Phức tạp hơn trong phân phối

## So sánh chi tiết

| Tiêu chí | Static Library | Dynamic Library |
|---------|---------------|----------------|
| File extension | `.a`, `.lib` | `.so`, `.dll`, `.dylib` |
| Kích thước file thực thi | Lớn | Nhỏ |
| Thời gian tải | Nhanh | Chậm hơn |
| Cập nhật | Phải biên dịch lại | Không cần biên dịch lại |
| Sử dụng bộ nhớ | Lãng phí nếu nhiều ứng dụng sử dụng | Tiết kiệm |
| Phức tạp khi phân phối | Đơn giản | Phức tạp |
| Hiệu năng runtime | Tối ưu hơn | Có thể chậm hơn do indirect calling |

## Khi nào sử dụng Static Library

- Khi hiệu năng là ưu tiên hàng đầu
- Khi không muốn lo lắng về dependency
- Cho các ứng dụng nhỏ, độc lập
- Khi không cần update thư viện thường xuyên

## Khi nào sử dụng Dynamic Library

- Khi cần tiết kiệm bộ nhớ
- Khi cần cập nhật thư viện mà không cần biên dịch lại
- Khi tạo plugin system
- Cho các ứng dụng lớn với nhiều thành phần

## Xem thêm

- [Cách tạo Static Library](./static_library.md)
- [Cách tạo Dynamic Library](./dynamic_library.md)
- [CMake và thư viện](./cmake_libraries.md)
