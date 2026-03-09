#include <iostream>
#include "libAudioFX/include/AudioFX.h" // Chỉ include file public

int main() {
    std::cout << "--- Chuong trinh test am thanh oto ---" << std::endl;

    // Goi ham tu thu vien tinh
    applyEqualizer();

    /* THỬ NGHIỆM LỖI:
       Nếu bạn bỏ comment dòng dưới đây, trình biên dịch sẽ báo lỗi 
       vì "secretFFTCalculation" là hàm nội bộ, khách hàng không được dùng.
    */
    // secretFFTCalculation(); 

    return 0;
}