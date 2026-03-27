#include <iostream>
#include <fstream>
#include <string>
class CamBien { virtual void read() {} }; // Lớp cha
class CamBienNhietDo : public CamBien {}; // Lớp con 1
class CamBienApSuat : public CamBien {};  // Lớp con 2

void kiemTraThietBi(CamBien* cb) {
    // Thử ép kiểu sang Cảm biến nhiệt độ
    CamBienNhietDo* t = dynamic_cast<CamBienNhietDo*>(cb);
    
    if (t) {
        std::cout << "Day la cam bien nhiet do!" << std::endl;
    } else {
        std::cout << "Khong phai cam bien nhiet do (tra ve nullptr)." << std::endl;
    }
}
int main(){
    CamBienApSuat apsuat;
    CamBienNhietDo nhietdo;
    CamBien* cb1 = &apsuat;
    CamBien* cb2= &nhietdo;
    kiemTraThietBi(cb1);
    kiemTraThietBi(cb2);
}