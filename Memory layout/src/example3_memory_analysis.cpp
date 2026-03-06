#include <iostream>
#include <iomanip>

// Hàm hiển thị chi tiết về bố cục bộ nhớ của một struct
void analyzeStructMemory() {
    struct SimpleStruct {
        char c;      // 1 byte
        int i;       // 4 bytes
        double d;    // 8 bytes
        char c2;     // 1 byte
    };
    
    struct PackedStruct {
        char c;
        int i;
        double d;
        char c2;
    } __attribute__((packed));  // Đánh dấu struct không có padding
    
    std::cout << "===== Phân tích bộ nhớ của struct =====\n" << std::endl;
    
    SimpleStruct s;
    PackedStruct ps;
    
    // Hiển thị kích thước và địa chỉ của từng thành phần
    std::cout << "Kích thước của SimpleStruct: " << sizeof(SimpleStruct) << " bytes" << std::endl;
    std::cout << "Địa chỉ của s: " << &s << std::endl;
    std::cout << "Địa chỉ của s.c: " << static_cast<void*>(&s.c) << " (offset: " << (reinterpret_cast<char*>(&s.c) - reinterpret_cast<char*>(&s)) << ")" << std::endl;
    std::cout << "Địa chỉ của s.i: " << &s.i << " (offset: " << (reinterpret_cast<char*>(&s.i) - reinterpret_cast<char*>(&s)) << ")" << std::endl;
    std::cout << "Địa chỉ của s.d: " << &s.d << " (offset: " << (reinterpret_cast<char*>(&s.d) - reinterpret_cast<char*>(&s)) << ")" << std::endl;
    std::cout << "Địa chỉ của s.c2: " << static_cast<void*>(&s.c2) << " (offset: " << (reinterpret_cast<char*>(&s.c2) - reinterpret_cast<char*>(&s)) << ")" << std::endl;
    
    std::cout << "\nKích thước của PackedStruct: " << sizeof(PackedStruct) << " bytes" << std::endl;
    std::cout << "Địa chỉ của ps: " << &ps << std::endl;
    std::cout << "Địa chỉ của ps.c: " << static_cast<void*>(&ps.c) << " (offset: " << (reinterpret_cast<char*>(&ps.c) - reinterpret_cast<char*>(&ps)) << ")" << std::endl;
    std::cout << "Địa chỉ của ps.i: " << &ps.i << " (offset: " << (reinterpret_cast<char*>(&ps.i) - reinterpret_cast<char*>(&ps)) << ")" << std::endl;
    std::cout << "Địa chỉ của ps.d: " << &ps.d << " (offset: " << (reinterpret_cast<char*>(&ps.d) - reinterpret_cast<char*>(&ps)) << ")" << std::endl;
    std::cout << "Địa chỉ của ps.c2: " << static_cast<void*>(&ps.c2) << " (offset: " << (reinterpret_cast<char*>(&ps.c2) - reinterpret_cast<char*>(&ps)) << ")" << std::endl;
    
    // Giải thích về memory padding và alignment
    std::cout << "\nGiải thích:" << std::endl;
    std::cout << "1. SimpleStruct có padding để đảm bảo alignment:" << std::endl;
    std::cout << "   - char c (1 byte) + padding (3 bytes)" << std::endl;
    std::cout << "   - int i (4 bytes)" << std::endl;
    std::cout << "   - double d (8 bytes)" << std::endl;
    std::cout << "   - char c2 (1 byte) + padding (7 bytes để đảm bảo alignment cho struct tiếp theo)" << std::endl;
    
    std::cout << "\n2. PackedStruct không có padding:" << std::endl;
    std::cout << "   - char c (1 byte)" << std::endl;
    std::cout << "   - int i (4 bytes)" << std::endl;
    std::cout << "   - double d (8 bytes)" << std::endl;
    std::cout << "   - char c2 (1 byte)" << std::endl;
}

// Hàm hiển thị thông tin chi tiết về mảng và con trỏ
void analyzeArrayMemory() {
    std::cout << "\n===== Phân tích bộ nhớ của mảng =====\n" << std::endl;
    
    int intArray[5] = {10, 20, 30, 40, 50};
    
    std::cout << "Địa chỉ của mảng (intArray): " << intArray << std::endl;
    std::cout << "Kích thước của mảng: " << sizeof(intArray) << " bytes" << std::endl;
    
    for (int i = 0; i < 5; i++) {
        std::cout << "Địa chỉ của intArray[" << i << "]: " << &intArray[i]
                  << ", Giá trị: " << intArray[i]
                  << ", Offset: " << (reinterpret_cast<char*>(&intArray[i]) - reinterpret_cast<char*>(intArray)) << " bytes" << std::endl;
    }
    
    // Phân tích mảng 2D
    std::cout << "\nMảng 2D:" << std::endl;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    std::cout << "Địa chỉ của mảng 2D (matrix): " << matrix << std::endl;
    std::cout << "Kích thước của mảng 2D: " << sizeof(matrix) << " bytes" << std::endl;
    
    for (int i = 0; i < 3; i++) {
        std::cout << "Địa chỉ của hàng " << i << " (matrix[" << i << "]): " << matrix[i] << std::endl;
        for (int j = 0; j < 4; j++) {
            std::cout << "  Địa chỉ của matrix[" << i << "][" << j << "]: " << &matrix[i][j]
                      << ", Giá trị: " << matrix[i][j] << std::endl;
        }
    }
}

// Hàm phân tích các kiểu dữ liệu
void analyzeDataTypes() {
    std::cout << "\n===== Kích thước các kiểu dữ liệu =====\n" << std::endl;
    
    std::cout << "char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "short: " << sizeof(short) << " bytes" << std::endl;
    std::cout << "int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "long: " << sizeof(long) << " bytes" << std::endl;
    std::cout << "long long: " << sizeof(long long) << " bytes" << std::endl;
    std::cout << "float: " << sizeof(float) << " bytes" << std::endl;
    std::cout << "double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "long double: " << sizeof(long double) << " bytes" << std::endl;
    std::cout << "bool: " << sizeof(bool) << " bytes" << std::endl;
    std::cout << "pointer: " << sizeof(void*) << " bytes" << std::endl;
}

// Hàm hiển thị bộ nhớ dưới dạng hex dump
void displayMemoryContent(const void* addr, size_t size) {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(addr);
    
    std::cout << "\n===== Hex Dump of Memory =====\n" << std::endl;
    std::cout << "Address       | Hex                                     | ASCII" << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    
    for (size_t i = 0; i < size; i += 16) {
        std::cout << std::setw(12) << static_cast<const void*>(p + i) << " | ";
        
        // Hiển thị giá trị hex
        for (size_t j = 0; j < 16; j++) {
            if (i + j < size) {
                std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(p[i + j]) << " ";
            } else {
                std::cout << "   ";
            }
        }
        
        std::cout << "| ";
        
        // Hiển thị giá trị ASCII
        for (size_t j = 0; j < 16; j++) {
            if (i + j < size) {
                char c = p[i + j];
                if (c >= 32 && c <= 126) {
                    std::cout << c;
                } else {
                    std::cout << ".";
                }
            } else {
                std::cout << " ";
            }
        }
        
        std::cout << std::dec << std::setfill(' ') << std::endl;
    }
}

int main() {
    analyzeStructMemory();
    analyzeArrayMemory();
    analyzeDataTypes();
    
    // Hiển thị nội dung bộ nhớ của một struct
    struct {
        int id;
        float value;
        char name[10];
    } sample = {42, 3.14f, "Hello"};
    
    displayMemoryContent(&sample, sizeof(sample));
    
    return 0;
}
