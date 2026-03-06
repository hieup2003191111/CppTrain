# C/C++ Library: Symbol Versioning, Inspection Tools, Symbol Visibility, dlfcn.h

## 1. Symbol Versioning

### Giải thích
Symbol versioning giúp quản lý các phiên bản hàm/thành phần trong thư viện động, tránh xung đột khi cập nhật hoặc mở rộng API.

### Ví dụ
- Tạo file `version_script.map`:
  ```text
  LIBRARY libmylib.so
  VERSION_1.0 {
      global: my_function_v1;
      local: *;
  };
  VERSION_2.0 {
      global: my_function_v2;
  } VERSION_1.0;
  ```
- Khai báo hàm trong mã nguồn:
  ```c
  // version.h
  void my_function_v1(void);
  void my_function_v2(void);
  // version.c
  void my_function_v1(void) { /* ... */ }
  void my_function_v2(void) { /* ... */ }
  ```
- Biên dịch với version script:
  ```sh
  gcc -shared -o libmylib.so version.c -Wl,--version-script=version_script.map
  ```
- Kiểm tra phiên bản ký hiệu:
  ```sh
  readelf --dyn-syms libmylib.so
  ```

## 2. Tools to Inspect Libraries and Executables

### Giải thích
Các công cụ sau giúp kiểm tra thông tin về thư viện và file thực thi:
- `ldd`: Liệt kê các thư viện động mà file thực thi phụ thuộc.
- `objdump`: Hiển thị thông tin chi tiết về file nhị phân (disassembly, symbol table...).
- `nm`: Liệt kê các ký hiệu (symbols) trong file object hoặc thư viện.
- `readelf`: Phân tích file ELF (Executable and Linkable Format).

### Ví dụ sử dụng
```sh
ldd ./my_app           # Xem các thư viện động liên kết
objdump -t libmylib.so # Xem bảng ký hiệu
nm libmylib.so         # Liệt kê các ký hiệu
readelf -s libmylib.so # Xem bảng ký hiệu động
```

## 3. Symbol Visibility

### Giải thích
Kiểm soát ký hiệu nào được export ra ngoài thư viện, ký hiệu nào chỉ dùng nội bộ.

### Ví dụ
```c
// core.h
__attribute__((visibility("default"))) void public_func();
__attribute__((visibility("hidden"))) void internal_func();
```

Thiết lập toàn cục khi biên dịch:
```sh
gcc -fvisibility=hidden -shared -o libmylib.so core.c
```
Chỉ các hàm có visibility "default" mới được export.

## 4. dlfcn.h Library

### Giải thích
`dlfcn.h` cho phép nạp thư viện động và lấy địa chỉ hàm tại runtime.

### Ví dụ
```c
#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("./libmylib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return 1;
    }
    void (*my_function)();
    *(void **) (&my_function) = dlsym(handle, "my_function_v1");
    if (!my_function) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    my_function(); // Gọi hàm từ thư viện động
    dlclose(handle);
    return 0;
}
```

### Giải thích
- `dlopen`: Nạp thư viện động.
- `dlsym`: Lấy địa chỉ hàm.
- `dlclose`: Giải phóng thư viện.
- `dlerror`: Lấy thông báo lỗi.

---

## Hướng dẫn sử dụng với CMake và Makefile

### CMake
- Tạo file `CMakeLists.txt` cho thư viện và ví dụ.
- Sử dụng `add_library`, `target_link_libraries`, `set_target_properties` để thiết lập visibility, versioning.

### Makefile
- Sử dụng các lệnh gcc như trên để build thư viện và ví dụ.
- Thêm mục kiểm tra với các tool như `nm`, `objdump`, `readelf`.

---

## Tham khảo
- [Symbol Versioning - GNU ld](https://sourceware.org/binutils/docs/ld/Symbol-Versioning.html)
- [Symbol Visibility - GCC](https://gcc.gnu.org/wiki/Visibility)
- [dlfcn.h - Dynamic Loading](https://man7.org/linux/man-pages/man3/dlopen.3.html)
