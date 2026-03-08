#include <iostream>
#include <windows.h> 

using namespace std;

// Hàm trả về địa chỉ của chuỗi hằng nằm trong vùng nhớ TEXT (Read-only)
const char* getFirmware() {
    return "V2.1.3-PROD"; 
}

void tryToModifyFirmware() {
    const char* version = getFirmware();
    
    cout << "1. Lay version thanh cong: " << version << endl;
    cout << "2. Dia chi vung nho cua chuoi nay la: " << (void*)version << endl;
    //(void*) để in ra địa chỉ,nếu không sẽ in ra chuỗi nội dung

    // Ép kiểu bỏ const bằng tà đạo const_cast
    char* nonConstVersion = const_cast<char*>(version);
    
    cout << "3. Da ep kieu xong. chuan bi ghi de chu 'X' vao vung Read-only..." << endl;
    cout << "   (Luu y: Chuong trinh se bi Windows dong ngay lap tuc sau dong nay!)" << endl;

    // --- DÒNG GÂY CRASH ---
    nonConstVersion[0] = 'X'; 

    // Dong nay se khong bao gio duoc in ra
    cout << "4. Thay doi thanh cong! Version moi: " << version << endl;
}

int main() {
    // Giúp Terminal hiển thị tiếng Việt
    SetConsoleOutputCP(65001);

    cout << "--- CHƯƠNG TRÌNH TEST VÙNG NHỚ READ-ONLY ---" << endl;
    cout << "Phien ban hien tai: " << getFirmware() << endl;
    cout << "--------------------------------------------" << endl;

    // Goi ham thu nghiem
    tryToModifyFirmware();

    cout << "--------------------------------------------" << endl;
    cout << "Neu ban thay dong nay, nghia la may ban khong co bao mat bo nho!" << endl;

    return 0;
}