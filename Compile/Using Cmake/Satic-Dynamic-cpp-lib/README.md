
# C/C++ Static và Dynamic Library

Repository này chứa tài liệu và ví dụ về cách tạo, sử dụng và quản lý Static (thư viện tĩnh) và Dynamic (thư viện động) Library trong C/C++.

## Cấu trúc thư mục

- **docs/**: Tài liệu chi tiết về Static và Dynamic Library
- **examples/**: Các ví dụ thực tế
  - **static_library/**: Ví dụ về cách tạo và sử dụng Static Library
  - **dynamic_library/**: Ví dụ về cách tạo và sử dụng Dynamic Library

## Bắt đầu

Xem file `docs/overview.md` để hiểu tổng quan về Static và Dynamic Library trong C/C++.

## Hướng dẫn sử dụng Static và Dynamic Library

### 1. Static Library (Thư viện tĩnh)

- Xem hướng dẫn chi tiết tại: [`docs/static_library.md`](docs/static_library.md)
- Thực hành với mã nguồn mẫu tại: [`examples/static_library/`](examples/static_library/)
- Quy trình tổng quát:
  1. Viết mã nguồn thư viện (`.h`, `.cpp`)
  2. Biên dịch thành object file và đóng gói thành static library (`.lib`/`.a`)
  3. Link static library vào chương trình chính khi biên dịch
  4. Xem hướng dẫn build và chạy trong `examples/static_library/README.md.in`

### 2. Dynamic Library (Thư viện động)

- Xem hướng dẫn chi tiết tại: [`docs/dynamic_library.md`](docs/dynamic_library.md)
- Thực hành với mã nguồn mẫu tại: [`examples/dynamic_library/`](examples/dynamic_library/)
- Quy trình tổng quát:
  1. Viết mã nguồn thư viện với macro export phù hợp (`.h`, `.cpp`)
  2. Biên dịch thành dynamic library (`.dll`/`.so`/`.dylib`)
  3. Link dynamic library vào chương trình chính hoặc nạp động khi chạy
  4. Xem hướng dẫn build và chạy trong `examples/dynamic_library/README.md.in`

## Ví dụ thực tế

Các thư mục ví dụ chứa mã nguồn, file CMake và hướng dẫn chi tiết để bạn dễ dàng xây dựng và chạy thử:

- **Static Library:**
  - Thư mục: `examples/static_library/`
  - Hướng dẫn: `examples/static_library/README.md.in`
- **Dynamic Library:**
  - Thư mục: `examples/dynamic_library/`
  - Hướng dẫn: `examples/dynamic_library/README.md.in`
- **Combined Usage (cả Static và Dynamic):**
  - Thư mục: `examples/combined_usage/`
  - Hướng dẫn: `examples/combined_usage/README.md.in`

## Yêu cầu

- C/C++ compiler (ví dụ: GCC, Clang, hoặc MSVC)
- CMake (để build các ví dụ)
