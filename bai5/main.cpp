#include <iostream>
#include <windows.h> 

// Khai báo prototype của hàm trong thư viện
void decodeFLAC();

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "[App] Khởi động trình phát nhạc ô tô..." << std::endl;
    decodeFLAC(); // Gọi hàm từ thư viện
    return 0;
}