#include <iostream>
#include <string>

// Giả lập struct Track
struct Track {
    std::string title;
};

// YÊU CẦU 1: Thiết kế lại hàm dùng Default Arguments
// Lưu ý: Giá trị mặc định thường được viết ở file header (.h) 
// hoặc trong lần khai báo đầu tiên của hàm.
void startPlayback(Track* track, int startTime = 0, int fadeInDuration = 0) {
    std::cout << "--- Bat dau phat nhac ---" << std::endl;
    std::cout << "Bai hat: " << track->title << std::endl;
    std::cout << "Vi tri bat dau: " << startTime << " ms" << std::endl;
    std::cout << "Thoi gian Fade-in: " << fadeInDuration << " ms" << std::endl;
    std::cout << "-------------------------\n" << std::endl;
}

int main() {
    Track mySong = {"Shape of You"};

    // YÊU CẦU 2: Minh họa 3 cách gọi
    
    // Cách A: Chi phat tu dau (Dung 2 gia tri mac dinh)
    startPlayback(&mySong);

    // Cách B: Fade-in 500ms (Phai dien tham so thu hai de den tham so thu ba)
    // Trình biên dịch hiểu: 0 là startTime, 500 là fadeInDuration
    startPlayback(&mySong, 0, 500);

    // Cách C: Bat dau tu 30s (30000ms) voi 1000ms fade-in
    startPlayback(&mySong, 30000, 1000);

    return 0;
}
//giải thích:khi truyền tham số gán giá trị mặc định 0,nó sẽ là optional parameter
//khi gọi có thể bỏ thiếu nó hoặc gán giá trị khác
//phân biệt default argument và overloading
//1:dùng khi logic giống nhau nhưng khác về tham số
//2:dùng khi logic bên trong khác nhau,tên hàm giống nhau