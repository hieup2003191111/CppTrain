#include <iostream>
#include <string>
#include <vector>
#include <chrono> // Thư viện để đo thời gian xử lý

// Định nghĩa cấu trúc dữ liệu lớn
struct SongMetadata {
    std::string title;
    std::string artist;
    std::string lyrics;
    // Giả lập dữ liệu ảnh bìa rất lớn (ví dụ: 10 triệu ký tự ~ 10MB)
    std::vector<char> albumArtRawData; 
};

// --- CÁCH 1: TRUYỀN THAM TRỊ (SAI - GÂY LAG) ---
// Mỗi lần gọi, máy tính phải copy 10MB dữ liệu này sang một ô nhớ mới
void displayMetadata_WRONG(SongMetadata data) {
    std::cout << "[Display] Dang hien thi: " << data.title << std::endl;
    // Việc copy dữ liệu diễn ra âm thầm trước khi vào hàm này
}

// --- CÁCH 2: TRUYỀN THAM CHIẾU HẰNG (ĐÚNG - TỐI ƯU) ---
// Chỉ truyền địa chỉ (8 byte), không copy dữ liệu, cực kỳ nhanh
void displayMetadata_OPTIMIZED(const SongMetadata& data) {
    std::cout << "[Display] Dang hien thi: " << data.title << std::endl;
    
    // data.title = "Hacked"; // LỖI BIÊN DỊCH: const ngăn chặn việc sửa đổi
}

int main() {
    // 1. Tạo một bài hát với dữ liệu "khủng"
    SongMetadata mySong;
    mySong.title = "Shape of You";
    mySong.artist = "Ed Sheeran";
    mySong.albumArtRawData.assign(10000000, 'x'); // Tạo 10MB dữ liệu giả

    std::cout << "--- Bat dau mo phong ---" << std::endl;

    // 2. Đo thời gian cách truyền Tham trị (Pass-by-value)
    auto start1 = std::chrono::high_resolution_clock::now();
    displayMetadata_WRONG(mySong);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time1 = end1 - start1;
    std::cout << "=> Thoi gian truyen THAM TRI: " << time1.count() << " ms (Cham do phai copy)\n" << std::endl;

    // 3. Đo thời gian cách truyền Tham chiếu hằng (Pass-by-const-ref)
    auto start2 = std::chrono::high_resolution_clock::now();
    displayMetadata_OPTIMIZED(mySong);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time2 = end2 - start2;
    std::cout << "=> Thoi gian truyen THAM CHIEU HANG: " << time2.count() << " ms (Gan nhu bang 0)\n" << std::endl;

    return 0;
}
//giải thích
//truyền const & chỉ có tác dụng in ra và ngăn copy