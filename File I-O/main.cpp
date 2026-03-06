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