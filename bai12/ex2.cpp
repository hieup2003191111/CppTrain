#include <iostream>

// Khai báo trước (Forward Declaration) để lớp CarAudioSystem biết sự tồn tại của Equalizer
class Equalizer;

class CarAudioSystem {
private:
    float hardware_volume; // Giá trị nhạy cảm: 0.0 đến 100.0
    int hardware_balance;  // -100 (Trái) đến 100 (Phải)

public:
    CarAudioSystem() : hardware_volume(10.0f), hardware_balance(0) {}

    // Phương thức public an toàn
    void setVolume(float v) {
        if (v >= 0.0f && v <= 50.0f) { // Giới hạn an toàn cho người dùng
            hardware_volume = v;
            std::cout << "Am luong nguoi dung dat: " << hardware_volume << std::endl;
        } else {
            std::cout << "Canh bao: Am luong vuot muc an toan!" << std::endl;
        }
    }

    // KHAI BÁO FRIEND: Cho phép Equalizer truy cập mọi thứ
    friend class Equalizer;
};

class Equalizer {
public:
    // Thuật toán phức tạp cần can thiệp sâu vào phần cứng
    void applyHeavyBassBoost(CarAudioSystem& system) {
        std::cout << "[Equalizer] Dang thuc hien tang Bass manh..." << std::endl;
        
        // Truy cập TRỰC TIẾP biến private mà không qua setVolume()
        // Equalizer có thể đặt mức volume > 50 (mức mà người dùng thường bị chặn)
        system.hardware_volume = 85.5f; 
        
        std::cout << "[Equalizer] Am luong phan cung hien tai: " 
                  << system.hardware_volume << std::endl;
    }
};

int main() {
    CarAudioSystem myCar;
    Equalizer myEq;

    // Người dùng bình thường bị giới hạn
    myCar.setVolume(80.0f); 

    // Equalizer (ban quản trị/hệ thống) có quyền can thiệp sâu
    myEq.applyHeavyBassBoost(myCar);

    return 0;
}
//giải thích:friend cho phép 1 số class đặc biệt truy cập vào private của 1 class khác
