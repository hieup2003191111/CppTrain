#include <iostream>
#include <cstring>
#include <memory>
#include <vector>

// 1. Memory Leak
void demonstrateMemoryLeak() {
    std::cout << "===== Memory Leak =====\n" << std::endl;
    
    // Cấp phát bộ nhớ nhưng không giải phóng
    int* leakedInt = new int(42);
    std::cout << "Allocated memory at " << leakedInt << " with value " << *leakedInt << std::endl;
    std::cout << "No delete call - this memory will be leaked" << std::endl;
    
    // Cấp phát trong vòng lặp (rất nguy hiểm)
    std::cout << "Allocating multiple objects without freeing (to simulate a severe leak)" << std::endl;
    for (int i = 0; i < 5; i++) {
        int* temp = new int(i);
        std::cout << "  Allocated at " << temp << " with value " << *temp << std::endl;
        // Không có delete => memory leak lớn trong thực tế
    }
    
    std::cout << "\nGiải pháp đúng - sử dụng smart pointers:" << std::endl;
    std::unique_ptr<int> smartInt = std::make_unique<int>(100);
    std::cout << "Smart pointer managing memory at " << smartInt.get() << " with value " << *smartInt << std::endl;
    std::cout << "Memory will be automatically freed when smartInt goes out of scope" << std::endl;
}

// 2. Dangling Pointer
void demonstrateDanglingPointer() {
    std::cout << "\n===== Dangling Pointer =====\n" << std::endl;
    
    // Tạo dangling pointer
    int* ptr = new int(10);
    std::cout << "Original pointer: " << ptr << " with value " << *ptr << std::endl;
    
    delete ptr;  // Giải phóng bộ nhớ
    std::cout << "Memory deleted" << std::endl;
    
    // ptr bây giờ là dangling pointer (trỏ đến vùng nhớ đã giải phóng)
    std::cout << "Dangling pointer still points to: " << ptr << std::endl;
    
    // Nguy hiểm: Truy cập vào vùng nhớ đã giải phóng
    std::cout << "NGUY HIỂM: Truy cập vào vùng nhớ đã giải phóng có thể gây crash hoặc kết quả không xác định" << std::endl;
    // std::cout << "Value: " << *ptr << std::endl;  // Uncomment to demonstrate crash
    
    // Giải pháp: Set pointer thành nullptr sau khi delete
    ptr = nullptr;
    std::cout << "After setting to nullptr: " << ptr << std::endl;
    if (ptr == nullptr) {
        std::cout << "Pointer is null, safe to check before using" << std::endl;
    }
}

// 3. Double Free
void demonstrateDoubleFree() {
    std::cout << "\n===== Double Free =====\n" << std::endl;
    
    int* ptr = new int(20);
    std::cout << "Allocated memory at " << ptr << " with value " << *ptr << std::endl;
    
    delete ptr;
    std::cout << "Memory deleted once" << std::endl;
    
    // Lỗi: Giải phóng bộ nhớ lần thứ hai
    std::cout << "NGUY HIỂM: Giải phóng bộ nhớ đã free sẽ gây lỗi nghiêm trọng" << std::endl;
    // delete ptr;  // Uncomment to demonstrate crash
    
    std::cout << "Giải pháp: Set pointer thành nullptr sau khi delete" << std::endl;
    ptr = nullptr;
    if (ptr == nullptr) {
        std::cout << "Safe: Cannot delete nullptr" << std::endl;
    }
}

// 4. Buffer Overflow
void demonstrateBufferOverflow() {
    std::cout << "\n===== Buffer Overflow =====\n" << std::endl;
    
    // Tạo một mảng 5 phần tử
    int buffer[5] = {1, 2, 3, 4, 5};
    
    std::cout << "Buffer allocated with 5 elements:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "buffer[" << i << "] = " << buffer[i] << " at " << &buffer[i] << std::endl;
    }
    
    // Nguy hiểm: Truy cập ngoài phạm vi của mảng
    std::cout << "\nNGUY HIỂM: Truy cập ngoài phạm vi mảng" << std::endl;
    std::cout << "Attempting to access buffer[7]..." << std::endl;
    // int value = buffer[7];  // Uncomment to demonstrate undefined behavior
    
    // Nguy hiểm: Ghi dữ liệu ngoài phạm vi mảng
    std::cout << "Attempting to write to buffer[7]..." << std::endl;
    // buffer[7] = 100;  // Uncomment to demonstrate undefined behavior
    
    std::cout << "\nGiải pháp: Sử dụng std::array hoặc std::vector với kiểm tra bounds" << std::endl;
    std::cout << "Ví dụ với std::vector:" << std::endl;
    
    std::vector<int> safeBuffer = {1, 2, 3, 4, 5};
    try {
        std::cout << "Safe access with .at(): " << safeBuffer.at(2) << std::endl;
        // Sẽ ném ngoại lệ thay vì gây undefined behavior
        // std::cout << safeBuffer.at(7) << std::endl;  // Uncomment to demonstrate exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught if index out of range: " << e.what() << std::endl;
    }
}

// 5. Use After Free
void demonstrateUseAfterFree() {
    std::cout << "\n===== Use After Free =====\n" << std::endl;
    
    // Tạo và khởi tạo một chuỗi
    char* str = new char[12];
    strcpy(str, "Hello World");
    std::cout << "String allocated at " << static_cast<void*>(str) << ": " << str << std::endl;
    
    // Giải phóng bộ nhớ
    delete[] str;
    std::cout << "Memory deleted" << std::endl;
    
    // NGUY HIỂM: Sử dụng bộ nhớ sau khi giải phóng
    std::cout << "NGUY HIỂM: Truy cập vào bộ nhớ sau khi giải phóng" << std::endl;
    // std::cout << "String after delete: " << str << std::endl;  // Uncomment to demonstrate undefined behavior
    
    std::cout << "\nGiải pháp: Sử dụng std::string hoặc smart pointers" << std::endl;
    std::string safeStr = "Hello World";
    std::cout << "Safe string: " << safeStr << std::endl;
}

// 6. Memory Fragmentation
void demonstrateMemoryFragmentation() {
    std::cout << "\n===== Memory Fragmentation =====\n" << std::endl;
    
    std::cout << "Minh họa quá trình gây phân mảnh bộ nhớ:" << std::endl;
    
    const int ALLOCS = 5;
    int* pointers[ALLOCS];
    
    // Cấp phát các khối bộ nhớ liên tiếp
    for (int i = 0; i < ALLOCS; i++) {
        pointers[i] = new int[10];
        std::cout << "Allocated block " << i << " at " << pointers[i] << std::endl;
    }
    
    // Giải phóng các khối bộ nhớ ở vị trí chẵn
    std::cout << "\nGiải phóng các khối ở vị trí chẵn:" << std::endl;
    for (int i = 0; i < ALLOCS; i += 2) {
        std::cout << "Freeing block " << i << " at " << pointers[i] << std::endl;
        delete[] pointers[i];
        pointers[i] = nullptr;
    }
    
    // Cấp phát lại bộ nhớ với kích thước khác nhau
    std::cout << "\nCấp phát lại bộ nhớ với kích thước khác:" << std::endl;
    for (int i = 0; i < ALLOCS; i += 2) {
        pointers[i] = new int[5];  // Kích thước nhỏ hơn
        std::cout << "Re-allocated block " << i << " at " << pointers[i] << std::endl;
    }
    
    // Giải phóng tất cả bộ nhớ
    std::cout << "\nGiải phóng tất cả bộ nhớ:" << std::endl;
    for (int i = 0; i < ALLOCS; i++) {
        if (pointers[i] != nullptr) {
            std::cout << "Freeing block " << i << " at " << pointers[i] << std::endl;
            delete[] pointers[i];
        }
    }
    
    std::cout << "\nPhân mảnh bộ nhớ xảy ra khi cấp phát và giải phóng bộ nhớ không đồng đều," << std::endl;
    std::cout << "dẫn đến các khoảng trống nhỏ không đủ để cấp phát cho các đối tượng lớn." << std::endl;
}

// 7. Null Pointer Dereference
void demonstrateNullPointerDereference() {
    std::cout << "\n===== Null Pointer Dereference =====\n" << std::endl;
    
    int* nullPtr = nullptr;
    std::cout << "nullPtr = " << nullPtr << std::endl;
    
    std::cout << "NGUY HIỂM: Truy cập vào null pointer sẽ gây crash" << std::endl;
    // std::cout << "Value: " << *nullPtr << std::endl;  // Uncomment to demonstrate crash
    
    std::cout << "\nGiải pháp: Luôn kiểm tra null trước khi truy cập" << std::endl;
    if (nullPtr != nullptr) {
        std::cout << "Safe to access" << std::endl;
    } else {
        std::cout << "Pointer is null, cannot access" << std::endl;
    }
}

int main() {
    std::cout << "===== DEMO CÁC VẤN ĐỀ PHỔ BIẾN VỀ BỘ NHỚ TRONG C++ =====\n" << std::endl;
    
    demonstrateMemoryLeak();
    demonstrateDanglingPointer();
    demonstrateDoubleFree();
    demonstrateBufferOverflow();
    demonstrateUseAfterFree();
    demonstrateMemoryFragmentation();
    demonstrateNullPointerDereference();
    
    return 0;
}
