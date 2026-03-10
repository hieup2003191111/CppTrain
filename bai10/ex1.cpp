#include <iostream>
#include <fstream>
//ghi dữ liệu vào 1 file binary
struct SimpleConfig {
    int id;      // 4 byte
    float vol;   // 4 byte
}; // Tổng cộng struct này chiếm 8 byte trong bộ nhớ

void save(const SimpleConfig& data, const char* fileName) {
    // Mở file: "out" để ghi, "binary" để ghi mã nhị phân (không phải văn bản)
    std::ofstream f(fileName, std::ios::out | std::ios::binary);
    
    if (f.is_open()) {
        // Ghi 8 byte dữ liệu từ địa chỉ của biến 'data' vào file
        f.write((char*)&data, sizeof(data)); 
        f.close();
        std::cout << "Da ghi 8 byte vao file " << fileName << std::endl;
    }
}

bool load(SimpleConfig& data, const char* fileName) {
    std::ifstream f(fileName, std::ios::in | std::ios::binary);
    
    if (f.is_open()) {
        // Đọc 8 byte từ file và nạp ngược lại vào vùng nhớ của biến 'data'
        f.read((char*)&data, sizeof(data));
        f.close();
        return true;
    }
    return false;
}

int main() {
    // 1. Chuẩn bị dữ liệu để ghi
    SimpleConfig configGui = {101, 0.85f};
    save(configGui, "test.bin");

    // 2. Chuẩn bị biến trống để nhận dữ liệu
    SimpleConfig configNhan = {0, 0.0f};
    if (load(configNhan, "test.bin")) {
        std::cout << "Ket qua sau khi doc file: ID = " << configNhan.id 
                  << ", Vol = " << configNhan.vol << std::endl;
    }

    return 0;
}