#include <iostream>
#include <vector>
#include <windows.h> // Thêm thư viện này
using namespace std;  
#include <stack> // Bước 1: Thêm thư viện ngăn xếp
//ham xu li anh
bool processAlbumArt(const string& imagePath){
    std::vector<char> imageBuffer(5*1024*1024);
    if (imagePath.empty()) return false;
    cout<<"dang xu li anh tu "<<imagePath<<endl;
    cout<<"kich thuoc cua vector tren heap la "<<imageBuffer.size()<<"byte"<<endl;
    return true;
    }

int main() {
    // Giúp Terminal hiển thị tiếng Việt (tùy chọn)
    SetConsoleOutputCP(65001);

    cout << "CHUONG TRINH MO PHONG XU LY ANH ALBUM" << endl;
    cout << "-------------------------------------" << endl;

    // Test với một đường dẫn ảnh giả lập
    string path = "C:/Music/AlbumArt/SummerHits.jpg";

    if (processAlbumArt(path)) {
        cout << "=> Ket qua: Thanh cong!" << endl;
    } else {
        cout << "=> Ket qua: That bai!" << endl;
    }

    cout << "-------------------------------------" << endl;
    cout << "Nhan Enter de thoat...";
    cin.get(); 

    return 0;
}