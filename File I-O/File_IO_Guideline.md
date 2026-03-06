# Guideline khi sử dụng File I/O trong C/C++ (Theo chuẩn AUTOSAR)

## 1. Nguyên tắc chung

- **Luôn kiểm tra lỗi**: Mọi thao tác mở, đọc, ghi, đóng file đều phải kiểm tra giá trị trả về.
- **Không dùng thư viện C chuẩn trong code AUTOSAR**: Tránh sử dụng trực tiếp `stdio.h` (fopen, fread, fwrite, fclose, ...). Nếu cần, hãy đóng gói qua abstraction layer hoặc wrapper.
- **Quản lý tài nguyên chặt chẽ**: Đảm bảo file luôn được đóng sau khi sử dụng, kể cả khi có lỗi (dùng cleanup hoặc finally block nếu có).
- **Không dùng file I/O trong các hàm thời gian thực (ISR, Task time-critical)**: File I/O thường chậm, không phù hợp cho các tác vụ real-time.
- **Đảm bảo thread-safety**: Nếu nhiều task truy cập cùng file, cần có cơ chế bảo vệ (mutex, semaphore).

## 2. Các bước thao tác File I/O

### a. Mở file

- Sử dụng wrapper function, ví dụ: `File_Open(const char* path, FileMode mode)`
- Kiểm tra giá trị trả về (con trỏ NULL hoặc mã lỗi).

### b. Đọc/Ghi file

- Đọc/ghi theo block, tránh đọc/ghi từng byte.
- Kiểm tra số byte thực tế đọc/ghi được.
- Xử lý trường hợp EOF hoặc lỗi.

### c. Đóng file

- Luôn đóng file sau khi sử dụng.
- Kiểm tra lỗi khi đóng file.

## 3. Coding Style

- Đặt tên biến, hàm rõ ràng: `fileHandle`, `File_ReadBlock`, ...
- Không hardcode đường dẫn file.
- Sử dụng macro hoặc config file cho các thông số liên quan đến file.

## 4. Lưu ý về AUTOSAR

- Nếu dùng OS hoặc MCAL layer, hãy sử dụng API chuẩn của AUTOSAR (nếu có).
- Không sử dụng file I/O trong các module safety-critical trừ khi được phép.
- Ghi chú rõ ràng về mục đích sử dụng file I/O trong tài liệu thiết kế.

## 5. Ví dụ (Pseudocode)

```c
FileHandle_t file = File_Open("data.bin", FILE_MODE_READ);
if (file == NULL) {
    // Xử lý lỗi mở file
}
uint8_t buffer[128];
int bytesRead = File_Read(file, buffer, sizeof(buffer));
if (bytesRead < 0) {
    // Xử lý lỗi đọc file
}
File_Close(file);
```

## 6. Checklist khi review code

- [ ] Có kiểm tra lỗi sau mỗi thao tác file?
- [ ] Có đóng file ở mọi trường hợp?
- [ ] Không dùng trực tiếp hàm stdio.h trong code AUTOSAR?
- [ ] Đảm bảo thread-safe nếu cần?
- [ ] Không dùng file I/O trong ISR hoặc task real-time?

## 7. Xử lý lỗi phổ biến trong File I/O (AUTOSAR)

### a. Các loại lỗi thường gặp

- **Lỗi mở file**: File không tồn tại, quyền truy cập bị từ chối, đường dẫn sai.
- **Lỗi đọc/ghi**: Đĩa đầy, file bị khóa, lỗi hardware, buffer overflow.
- **Lỗi đóng file**: File đã bị đóng trước đó hoặc lỗi hệ thống.
- **Lỗi seek**: Vị trí seek vượt quá kích thước file hoặc không hợp lệ.

### b. Cách xử lý lỗi theo AUTOSAR

- **Sử dụng error codes**: Định nghĩa enum cho các mã lỗi (e.g., FILE_ERROR_OPEN_FAILED, FILE_ERROR_READ_FAILED).
- **Logging và reporting**: Ghi log lỗi vào hệ thống AUTOSAR (Dem, Det modules) để debug.
- **Recovery mechanisms**: Thử lại thao tác (retry), chuyển sang file backup, hoặc chuyển sang safe state.
- **Resource cleanup**: Luôn giải phóng tài nguyên (đóng file, free buffer) ngay cả khi lỗi.
- **Thread-safety trong xử lý lỗi**: Sử dụng mutex để bảo vệ shared resources khi report lỗi.

### c. Ví dụ xử lý lỗi

```c
typedef enum {
    FILE_OK = 0,
    FILE_ERROR_OPEN_FAILED,
    FILE_ERROR_READ_FAILED,
    FILE_ERROR_WRITE_FAILED,
    FILE_ERROR_CLOSE_FAILED
} FileError_t;

FileError_t File_ReadSafe(FileHandle_t handle, void* buffer, uint32_t size, uint32_t* bytesRead) {
    if (handle == NULL || buffer == NULL) {
        return FILE_ERROR_READ_FAILED;
    }
    int32_t result = File_Read(handle, buffer, size);
    if (result < 0) {
        // Log error to AUTOSAR Dem
        Dem_ReportError(DemConf_DemEventParameter_FileReadError);
        return FILE_ERROR_READ_FAILED;
    }
    *bytesRead = (uint32_t)result;
    return FILE_OK;
}
```

### d. Lưu ý đặc biệt cho AUTOSAR

- **Safety-critical systems**: File I/O thường không được dùng trong ASIL D modules. Nếu dùng, phải có redundancy và error recovery.
- **Real-time constraints**: Xử lý lỗi không được block quá lâu; dùng timeout cho các thao tác.
- **Compliance với MISRA C**: Tránh undefined behavior, kiểm tra NULL pointers, tránh buffer overflows.
- **Testing**: Unit test cho các trường hợp lỗi (mock file system errors).

## 8. Ví dụ cụ thể và Template Wrapper

Dưới đây là template wrapper hoàn chỉnh cho File I/O, tuân thủ AUTOSAR với error handling. Các file được tạo trong workspace:

### a. FileIOWrapper.h (Header)

```cpp
#ifndef FILE_IO_WRAPPER_H
#define FILE_IO_WRAPPER_H

#include <stdint.h>

// Typedefs for AUTOSAR compliance
typedef void* FileHandle_t;
typedef enum {
    FILE_MODE_READ = 0,
    FILE_MODE_WRITE,
    FILE_MODE_APPEND,
    FILE_MODE_READ_WRITE
} FileMode_t;

typedef enum {
    FILE_OK = 0,
    FILE_ERROR_OPEN_FAILED,
    FILE_ERROR_READ_FAILED,
    FILE_ERROR_WRITE_FAILED,
    FILE_ERROR_CLOSE_FAILED,
    FILE_ERROR_SEEK_FAILED,
    FILE_ERROR_INVALID_PARAM
} FileError_t;

// Function declarations
FileError_t File_Open(const char* path, FileMode_t mode, FileHandle_t* handle);
FileError_t File_Read(FileHandle_t handle, void* buffer, uint32_t size, uint32_t* bytesRead);
FileError_t File_Write(FileHandle_t handle, const void* buffer, uint32_t size, uint32_t* bytesWritten);
FileError_t File_Close(FileHandle_t handle);
FileError_t File_Seek(FileHandle_t handle, int32_t offset, int whence);

#endif // FILE_IO_WRAPPER_H
```

### b. FileIOWrapper.cpp (Implementation)

```cpp
#include "FileIOWrapper.h"
#include <stdio.h>  // Note: In AUTOSAR, this should be abstracted via MCAL/OS layer
#include <stdlib.h>

// Internal mapping of modes to stdio modes
static const char* modeStrings[] = {
    "rb",  // FILE_MODE_READ
    "wb",  // FILE_MODE_WRITE
    "ab",  // FILE_MODE_APPEND
    "rb+"  // FILE_MODE_READ_WRITE
};

FileError_t File_Open(const char* path, FileMode_t mode, FileHandle_t* handle) {
    if (path == NULL || mode >= sizeof(modeStrings)/sizeof(modeStrings[0]) || handle == NULL) {
        return FILE_ERROR_INVALID_PARAM;
    }
    FILE* file = fopen(path, modeStrings[mode]);
    if (file == NULL) {
        return FILE_ERROR_OPEN_FAILED;
    }
    *handle = (FileHandle_t)file;
    return FILE_OK;
}

FileError_t File_Read(FileHandle_t handle, void* buffer, uint32_t size, uint32_t* bytesRead) {
    if (handle == NULL || buffer == NULL || bytesRead == NULL) {
        return FILE_ERROR_INVALID_PARAM;
    }
    FILE* file = (FILE*)handle;
    size_t result = fread(buffer, 1, size, file);
    if (result != size && !feof(file)) {
        return FILE_ERROR_READ_FAILED;
    }
    *bytesRead = (uint32_t)result;
    return FILE_OK;
}

FileError_t File_Write(FileHandle_t handle, const void* buffer, uint32_t size, uint32_t* bytesWritten) {
    if (handle == NULL || buffer == NULL || bytesWritten == NULL) {
        return FILE_ERROR_INVALID_PARAM;
    }
    FILE* file = (FILE*)handle;
    size_t result = fwrite(buffer, 1, size, file);
    if (result != size) {
        return FILE_ERROR_WRITE_FAILED;
    }
    *bytesWritten = (uint32_t)result;
    return FILE_OK;
}

FileError_t File_Close(FileHandle_t handle) {
    if (handle == NULL) {
        return FILE_ERROR_INVALID_PARAM;
    }
    FILE* file = (FILE*)handle;
    if (fclose(file) != 0) {
        return FILE_ERROR_CLOSE_FAILED;
    }
    return FILE_OK;
}

FileError_t File_Seek(FileHandle_t handle, int32_t offset, int whence) {
    if (handle == NULL) {
        return FILE_ERROR_INVALID_PARAM;
    }
    FILE* file = (FILE*)handle;
    if (fseek(file, offset, whence) != 0) {
        return FILE_ERROR_SEEK_FAILED;
    }
    return FILE_OK;
}
```

### c. main.cpp (Ví dụ sử dụng)

```cpp
#include "FileIOWrapper.h"
#include <iostream>
#include <cstring>

int main() {
    FileHandle_t fileHandle;
    FileError_t error;

    // Example 1: Writing to a file
    error = File_Open("example.txt", FILE_MODE_WRITE, &fileHandle);
    if (error != FILE_OK) {
        std::cout << "Error opening file for writing: " << error << std::endl;
        return -1;
    }

    const char* data = "Hello, AUTOSAR File I/O!";
    uint32_t bytesWritten;
    error = File_Write(fileHandle, data, strlen(data), &bytesWritten);
    if (error != FILE_OK) {
        std::cout << "Error writing to file: " << error << std::endl;
    } else {
        std::cout << "Written " << bytesWritten << " bytes to file" << std::endl;
    }

    File_Close(fileHandle);

    // Example 2: Reading from a file
    error = File_Open("example.txt", FILE_MODE_READ, &fileHandle);
    if (error != FILE_OK) {
        std::cout << "Error opening file for reading: " << error << std::endl;
        return -1;
    }

    char buffer[256];
    uint32_t bytesRead;
    error = File_Read(fileHandle, buffer, sizeof(buffer) - 1, &bytesRead);
    if (error != FILE_OK) {
        std::cout << "Error reading from file: " << error << std::endl;
    } else {
        buffer[bytesRead] = '\0';  // Null-terminate
        std::cout << "Read from file: " << buffer << std::endl;
    }

    File_Close(fileHandle);

    // Example 3: Seeking and partial read
    error = File_Open("example.txt", FILE_MODE_READ, &fileHandle);
    if (error == FILE_OK) {
        error = File_Seek(fileHandle, 7, SEEK_SET);  // Skip "Hello, "
        if (error != FILE_OK) {
            std::cout << "Error seeking in file: " << error << std::endl;
        } else {
            char partialBuffer[50];
            error = File_Read(fileHandle, partialBuffer, sizeof(partialBuffer) - 1, &bytesRead);
            if (error == FILE_OK && bytesRead > 0) {
                partialBuffer[bytesRead] = '\0';
                std::cout << "Partial read: " << partialBuffer << std::endl;
            }
        }
        File_Close(fileHandle);
    }

    return 0;
}
```