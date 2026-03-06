#ifndef FB384F97_7BDE_409B_BDCD_74BE31A3D389
#define FB384F97_7BDE_409B_BDCD_74BE31A3D389
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


#endif /* FB384F97_7BDE_409B_BDCD_74BE31A3D389 */
