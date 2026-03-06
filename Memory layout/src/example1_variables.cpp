#include <iostream>

// Biến toàn cục trong Data segment (đã khởi tạo)
int globalVar = 10;

// Biến toàn cục trong BSS segment (chưa khởi tạo)
int uninitGlobalVar;

// Hằng số trong Text/Read-only segment
const int constVar = 100;

// Biến tĩnh trong Data segment
static int staticVar = 50;

void demoLocalVars() {
    // Biến cục bộ trong Stack
    int localVar = 5;
    
    // Cấp phát động từ Heap
    int* heapVar = new int(20);
    
    std::cout << "Địa chỉ của biến toàn cục (Data): " << &globalVar << std::endl;
    std::cout << "Địa chỉ của biến toàn cục chưa khởi tạo (BSS): " << &uninitGlobalVar << std::endl;
    std::cout << "Địa chỉ của hằng số (Read-only): " << &constVar << std::endl;
    std::cout << "Địa chỉ của biến tĩnh (Data): " << &staticVar << std::endl;
    std::cout << "Địa chỉ của biến cục bộ (Stack): " << &localVar << std::endl;
    std::cout << "Địa chỉ của biến cấp phát động (Heap): " << heapVar << std::endl;
    std::cout << "Địa chỉ của con trỏ (Stack): " << &heapVar << std::endl;
    
    // Giải phóng bộ nhớ Heap
    delete heapVar;
}

void recursiveFunction(int depth) {
    // Tạo một mảng lớn trên Stack
    char buffer[1024];
    
    std::cout << "Độ sâu đệ quy: " << depth << ", Địa chỉ của buffer: " << static_cast<void*>(buffer) << std::endl;
    
    // Dừng đệ quy khi độ sâu > 5 để tránh stack overflow
    if (depth < 5) {
        recursiveFunction(depth + 1);
    }
}

int main() {
    std::cout << "===== Minh họa về bố cục bộ nhớ trong C++ =====\n" << std::endl;
    
    demoLocalVars();
    
    std::cout << "\n===== Minh họa Stack trong đệ quy =====\n" << std::endl;
    
    recursiveFunction(1);
    
    return 0;
}
