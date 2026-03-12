#include <iostream>
#include "AudioManager.h"
#include "UIManager.h"
#include "DBManager.h"

// Yêu cầu 3 (Giải thích): Không nên dùng "using namespace UI;" ở đây (phạm vi toàn cục)
// vì nó sẽ làm mất ý nghĩa của việc chia namespace và dễ gây xung đột tên.

int main() {
    // --- YÊU CẦU 2: Sử dụng Fully Qualified Names ---
    // Khai báo 3 đối tượng Manager khác nhau mà không bị lỗi trùng tên
    Audio::Manager audioMgr;
    UI::Manager    uiMgr;
    DB::Manager    dbMgr;

    std::cout << "--- Khoi tao bang ten day du: ---\n";
    audioMgr.display(); // Sẽ gọi Manager của Audio
    uiMgr.display();    // Sẽ gọi Manager của UI
    dbMgr.display();    // Sẽ gọi Manager của DB

    // --- YÊU CẦU 3: Sử dụng 'using' trong phạm vi hàm ---
    std::cout << "\n--- Su dung 'using' trong ham: ---\n";
    {
        // Chỉ định nghĩa Manager trong khối lệnh này là DB::Manager
        using DB::Manager; 
        
        Manager tempDBMgr; // Không cần tiền tố DB:: nữa
        tempDBMgr.display();
    }
    // Ra khỏi dấu }, 'Manager' sẽ không còn được nhận diện tự động nữa.

    return 0;
}