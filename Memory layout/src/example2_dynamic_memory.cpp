#include <iostream>
#include <vector>
#include <memory>  // Thêm dòng này để dùng unique_ptr
// Hàm minh họa cấp phát và giải phóng bộ nhớ trong C
void cStyleMemoryManagement() {
    std::cout << "===== Quản lý bộ nhớ kiểu C =====\n" << std::endl;
    
    // Cấp phát một số nguyên
    int* singleInt = (int*)malloc(sizeof(int));
    *singleInt = 42;
    std::cout << "Single int allocated with malloc: " << *singleInt << std::endl;
    std::cout << "Address: " << singleInt << std::endl;
    
    // Cấp phát một mảng các số nguyên
    int* intArray = (int*)malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        intArray[i] = i * 10;
    }
    std::cout << "Array allocated with malloc: ";
    for (int i = 0; i < 5; i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Starting address: " << intArray << std::endl;
    
    // Thay đổi kích thước mảng
    intArray = (int*)realloc(intArray, 10 * sizeof(int));
    for (int i = 5; i < 10; i++) {
        intArray[i] = i * 10;
    }
    std::cout << "Array after realloc: ";
    for (int i = 0; i < 10; i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "New address: " << intArray << std::endl;
    
    // Cấp phát và khởi tạo bằng 0
    int* zeroArray = (int*)calloc(5, sizeof(int));
    std::cout << "Array allocated with calloc: ";
    for (int i = 0; i < 5; i++) {
        std::cout << zeroArray[i] << " ";
    }
    std::cout << std::endl;
    
    // Giải phóng bộ nhớ
    free(singleInt);
    free(intArray);
    free(zeroArray);
    
    std::cout << std::endl;
}

// Hàm minh họa cấp phát và giải phóng bộ nhớ trong C++
void cppStyleMemoryManagement() {
    std::cout << "===== Quản lý bộ nhớ kiểu C++ =====\n" << std::endl;
    
    // Cấp phát một đối tượng
    int* singleInt = new int(42);
    std::cout << "Single int allocated with new: " << *singleInt << std::endl;
    std::cout << "Address: " << singleInt << std::endl;
    
    // Cấp phát một mảng
    int* intArray = new int[5];
    for (int i = 0; i < 5; i++) {
        intArray[i] = i * 10;
    }
    std::cout << "Array allocated with new[]: ";
    for (int i = 0; i < 5; i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    
    // Sử dụng vector (cấp phát động tự động)
    std::vector<int> vec;
    std::cout << "Vector initial capacity: " << vec.capacity() << std::endl;
    
    for (int i = 0; i < 10; i++) {
        vec.push_back(i * 5);
        std::cout << "After adding element " << i << ": Size = " << vec.size() 
                  << ", Capacity = " << vec.capacity() << std::endl;
    }
    
    std::cout << "Vector elements: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Smart pointers
    std::cout << "\n===== Smart Pointers =====\n" << std::endl;
    
    {
        std::cout << "Entering scope with unique_ptr" << std::endl;
        std::unique_ptr<int> uniquePtr(new int(100));
        std::cout << "unique_ptr value: " << *uniquePtr << std::endl;
        std::cout << "Leaving scope - unique_ptr will be automatically deleted" << std::endl;
    }
    
    // Giải phóng bộ nhớ
    delete singleInt;
    delete[] intArray;  // Lưu ý: sử dụng delete[] cho mảng
}

// Hàm minh họa memory leak
void demonstrateMemoryLeak() {
    std::cout << "===== Minh họa Memory Leak =====\n" << std::endl;
    
    std::cout << "Allocating memory without freeing it (memory leak)" << std::endl;
    int* leakyMemory = new int(999);
    std::cout << "Memory address: " << leakyMemory << " with value: " << *leakyMemory << std::endl;
    
    // Không có delete ở đây => memory leak
    std::cout << "No delete call - this memory will be leaked" << std::endl;
}

int main() {
    cStyleMemoryManagement();
    cppStyleMemoryManagement();
    demonstrateMemoryLeak();
    
    return 0;
}
