#include <iostream>
using namespace std;
int b;
// Hàm tạo "rác" trên bộ nhớ Stack
void make_trash2() {
    int a = 999; // Giá trị này sẽ nằm lại trên ô nhớ sau khi hàm kết thúc
}
void make_trash() {
    int a = 9999; // Giá trị này sẽ nằm lại trên ô nhớ sau khi hàm kết thúc
}

// Giả lập đọc file thất bại
bool load(int &v) {
    return false; // Không ghi đè giá trị mới vào v
}

void test_unsafe() {
    int vol; // LỖI: Khai báo nhưng không khởi tạo
    cout<<"vol:"<<vol<<endl;
    
    load(vol); // vol vẫn giữ giá trị rác vì load trả về false

    cout << "  Unsafe Vol: " << vol << " (RAC)"; 
    cout << " b:"<<b<<endl; 
}

void test_safe() {
    int vol = 20; // ĐÚNG: Khởi tạo giá trị mặc định an toàn
    
    load(vol); // Nếu load lỗi, vol vẫn là 20

    cout << "Safe Vol: " << vol;
    cout << " b: "<<b<<endl;
}

int main() {
    make_trash();   // Làm bẩn bộ nhớ
    make_trash2();
    test_unsafe();  // In ra số ngẫu nhiên nguy hiểm
    test_safe();    // Luôn in ra 20
    return 0;
}