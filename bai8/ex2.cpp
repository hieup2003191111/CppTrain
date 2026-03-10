#include <iostream>  
#include <vector>  
#include <string>  
#include <windows.h> 
#include <list>
using namespace std;
//    SetConsoleOutputCP(65001);
//alias
typedef void(*AudioEffectCallback)(float* buffer,size_t size)  ;
enum EffectType{bass,reverb,none};
void applyBassBoost(float* buffer,size_t size){
    cout<<"dang xu li bass"<<endl;
    for(int i=0;i<size;i++){
        buffer[i]*=1.5f;
    }
}
void applyReverb(float* buffer,size_t size){
    cout<<"dang xu li reverb"<<endl;
    for(int i=0;i<size;i++){
        buffer[i]*=0.5f;
    }
}
void applyNoEffect(float* buffer, size_t size) {
    std::cout << "[Effect] Khong dung hieu ung.\n";
}
class AudioProcessor{
public:
    AudioEffectCallback activeEffect;//khai báo 1 con trỏ hàm
    //con trỏ hàm chỉ có thể gọi đến hàm cùng kiểu tham số
    AudioProcessor(){
        activeEffect = applyNoEffect;
    }
    void SetEffect(EffectType type){
        switch(type)
        {
            case bass:
            activeEffect = applyBassBoost;
            break;
            case reverb:
            activeEffect = applyReverb;
            break;
            case none:
            activeEffect = applyNoEffect;
            default:
            cout<<"du lieu khong hop le"<<endl;

        }
    }
};
int main() {
    SetConsoleOutputCP(65001);
    // 1. Giả lập một đoạn dữ liệu âm thanh (buffer)
    float myAudio[5] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
    size_t size = 5;

    // 2. Khởi tạo bộ xử lý
    AudioProcessor processor;

    // 3. Hiển thị menu cho người dùng
    int choice;
    std::cout << "===== HE THONG AM THANH O TO =====" << std::endl;
    std::cout << "Chon hieu ung am thanh ban muon:" << std::endl;
    std::cout << "0. Bass Boost (Tang am tram)" << std::endl;
    std::cout << "1. Reverb (Am vang)" << std::endl;
    std::cout << "2. No Effect (Khong hieu ung)" << std::endl;
    std::cout << "Nhap lua chon cua ban (0-2): ";
    
    // Nhận số nguyên từ bàn phím
    std::cin >> choice;

    // 4. Ép kiểu từ int sang EffectType và thiết lập hiệu ứng
    // Chúng ta ép kiểu: (EffectType)choice
    if (choice >= 0 && choice <= 2) {
        processor.SetEffect(static_cast<EffectType>(choice));
    } else {
        std::cout << "Lua chon khong hop le! Dang dung mac dinh." << std::endl;
        processor.SetEffect(none);
    }

    // 5. Chạy vòng lặp xử lý âm thanh
    std::cout << "\n--- Dang bat dau xu ly am thanh ---" << std::endl;
    processor.activeEffect(myAudio, size);//kích hoạt con trỏ hàm

    // In kết quả sau khi xử lý để kiểm tra
    std::cout << "Du lieu sau khi xử ly: ";
    for(size_t i = 0; i < size; ++i) {
        std::cout << myAudio[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}