#include <iostream>

class UIWidget {
public:
    virtual void draw() { std::cout << "Drawing Widget\n"; }
    virtual ~UIWidget() {}
};

class Button : public UIWidget {
public:
    // override giúp tránh lỗi typo 'draaw'
    void draw() override { std::cout << "Drawing Button\n"; }
};

// final giúp bảo vệ kiến trúc, không cho ai can thiệp vào lớp bảo mật này nữa
class SecurityButton  : public Button {
public:
     void draw() override final{ std::cout << "Drawing Security Button (Safe)\n"; }
};
//không cho kế thừa khi final class
// class MyHackButton : public SecurityButton {
// };
//không cho sửa khi final method
// class CreativeButton : public SecurityButton {
// public:
//     // THỬ NGHIỆM LỖI:
//     void draw() override { // <--- LỖI BIÊN DỊCH
//         std::cout << "Toi muon ve kieu khac"; 
//     }
//     // Lỗi: "declaration of 'draw' overrides a 'final' function"
// };



int main() {
    UIWidget* ui = new SecurityButton();
    ui->draw(); // Chắc chắn gọi đúng hàm của SecurityButton
    delete ui;
    return 0;
}