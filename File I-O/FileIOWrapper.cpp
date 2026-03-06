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