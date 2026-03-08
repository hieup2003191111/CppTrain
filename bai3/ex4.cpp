#include <iostream>

using namespace std;

// Khai báo một mảng cực lớn (500.000 phần tử)
// Chúng ta KHÔNG cho nó giá trị ban đầu (Uninitialized)
// int mang_khong_lo[500000]={1,5}; 
// int mang_khong_lo[500000]={0};
int mang_khong_lo[500000]; 
int main() {
    // 1. Tính toán dung lượng thực tế trong RAM
    // Mỗi số int chiếm 4 bytes
    long long tong_byte = sizeof(mang_khong_lo);
    double mb = tong_byte / (1024.0 * 1024.0);

    cout << "Mang nay chiem trong RAM: " << mb << " MB" << endl;

    // 2. Chứng minh nó tự động bằng 0 (Đặc điểm của BSS)
    cout << "Gia tri phan tu dau tien: " << mang_khong_lo[0] << endl;

    return 0;
}