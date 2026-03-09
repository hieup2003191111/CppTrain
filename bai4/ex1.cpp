#include <iostream>
#include <vector>
#include <windows.h> 

using namespace std;

// 1. Prototype đúng chuẩn (kết thúc bằng dấu chấm phẩy)
void initA();
void initB();
void initHardWare();

int main() {
    SetConsoleOutputCP(65001); // Hiển thị tiếng Việt
    initHardWare();
    return 0;
}

// 2. Định nghĩa hàm initHardWare
void initHardWare() {
    #ifdef MODEL_S
        initA();
    #elif defined(MODEL_X) // Dùng defined(MODEL_X) cho chuẩn xác
        initB();
    #else 
        #error "Loi: Ban phai xac dinh MODEL_S hoac MODEL_X khi bien dich!" 
    #endif 
}

// 3. Định nghĩa chi tiết các hàm Driver
void initA() { 
    cout << "Dang khoi tao chip am thanh NVIDIA cho Model S..." << endl; 
}

void initB() { 
    cout << "Dang khoi tao chip am thanh BOSCH cho Model X..." << endl; 
}