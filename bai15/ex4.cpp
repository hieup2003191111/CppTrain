#include <iostream>
#include <fstream>
#include <string>

// --- Yêu cầu 1: Base Template (Cho các kiểu POD như int, float) ---
template <typename T>
void serialize(std::ostream& stream, const T& data) {
    std::cout << "[Base Template] Serializing POD data...\n";
    stream.write(reinterpret_cast<const char*>(&data), sizeof(T));
}

// --- Yêu cầu 2: Specialization cho std::string ---
// Cú pháp: template <> void tên_hàm<kiểu_chuyên_biệt>
template <>
void serialize<std::string>(std::ostream& stream, const std::string& data) {
    std::cout << "[Specialization] Serializing std::string...\n";
    
    // 1. Ghi độ dài chuỗi (để khi đọc lại biết cần đọc bao nhiêu ký tự)
    size_t length = data.length();
    stream.write(reinterpret_cast<const char*>(&length), sizeof(length));
    
    // 2. Ghi nội dung thực sự của chuỗi
    stream.write(data.c_str(), length);
}

// Struct Song để test
struct Song {
    int id;
    std::string title;
};

// --- Yêu cầu 3: Specialization cho Song ---
template <>
void serialize<Song>(std::ostream& stream, const Song& song) {
    std::cout << "[Specialization] Serializing Song object...\n";
    // Gọi các hàm serialize tương ứng cho từng thành viên
    serialize<int>(stream, song.id);         // Sẽ dùng Base Template
    serialize<std::string>(stream, song.title); // Sẽ dùng Specialization cho string
}

int main() {
    std::ofstream outFile("data.bin", std::ios::binary);

    int myID = 100;
    Song mySong = {200, "Hello World"};

    // Yêu cầu 4: Trình biên dịch tự chọn phiên bản phù hợp
    serialize(outFile, myID);   // Gọi Base vì int là POD
    serialize(outFile, mySong); // Gọi Specialization cho Song

    outFile.close();
    std::cout << "\nSerialization completed to data.bin\n";
    return 0;
}