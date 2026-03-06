#include <iostream>
using namespace std;
int main(){
    int hardware_variable = 100;
    int a = 10;
    const volatile int * const  i = &hardware_variable;
    //const 1: cố định giá trị của vùng nhớ mà con trỏ lưu giữ
    //volatile : tránh biên dịch tối ưu hoá code,bắt buộc đọc từ bộ nhớ(không đọc từ thanh ghi như thông thường)
    //const 2: không cho phép trỏ đi chỗ khác
    cout<<"gia tri thanh ghi la : "<<*i<<endl;
    // cout<<"test thay doi gia tri "<<endl;
    //*i=10;(error)
    // i=&a;(error)
    // cout<<"gia tri thanh ghi la : "<<*i<<endl;
    return 0;
}