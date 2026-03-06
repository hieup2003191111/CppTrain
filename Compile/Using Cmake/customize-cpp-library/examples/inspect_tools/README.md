# Inspect Tools Example

## Mục đích
Hướng dẫn sử dụng các công cụ kiểm tra thư viện và file thực thi: `ldd`, `objdump`, `nm`, `readelf`.

## Ví dụ
Giả sử bạn đã build được file thực thi `main` và thư viện động `libdynlib.so` từ ví dụ dlfcn:

### Kiểm tra các thư viện liên kết
```sh
ldd ./main
```

### Xem bảng ký hiệu
```sh
nm libdynlib.so
objdump -t libdynlib.so
readelf -s libdynlib.so
```

## Giải thích
- `ldd`: Liệt kê các thư viện động mà file thực thi phụ thuộc.
- `nm`: Liệt kê các ký hiệu (symbols).
- `objdump -t`: Hiển thị bảng ký hiệu.
- `readelf -s`: Hiển thị bảng ký hiệu động.
