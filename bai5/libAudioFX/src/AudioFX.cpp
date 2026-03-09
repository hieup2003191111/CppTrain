#include "AudioFX.h"       // Thư viện thấy file Public
#include "internal_math.h" // Thư viện thấy file Private
#include <iostream>

void applyEqualizer() {
    secretFFTCalculation(); // Gọi hàm nội bộ
    std::cout << "Da thuc hien Equalizer!" << std::endl;
}

void secretFFTCalculation() {
    std::cout << "Dang tinh toan ma tran FFT noi bo..." << std::endl;
}