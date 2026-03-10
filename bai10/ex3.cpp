#include <iostream>
#include <fstream>
#include <vector>

const int CHUNK_SIZE = 4096; // 4KB mỗi lần đọc
const int WAV_HEADER_SIZE = 44; // Kích thước header tiêu chuẩn của file .wav

void playAudioFile(const char* filepath) {
    // 1. Mở file ở chế độ nhị phân
    std::ifstream audioFile(filepath, std::ios::in | std::ios::binary);

    if (!audioFile.is_open()) {
        std::cerr << "Loi: Khong the mo file am thanh: " << filepath << std::endl;
        return;
    }

    // 2. Nhảy qua Header để đến phần dữ liệu thô (Raw Data)
    // seekg: seek get (di chuyển con trỏ đọc)
    audioFile.seekg(WAV_HEADER_SIZE, std::ios::beg);
    std::cout << "--- Bat dau phat nhac (da bo qua header 44 bytes) ---" << std::endl;

    // Tạo buffer (bộ nhớ tạm) để chứa 4KB dữ liệu mỗi lần đọc
    char buffer[CHUNK_SIZE];
    long totalBytesRead = 0;

    // 3. Vòng lặp đọc dữ liệu cho đến hết file
    while (!audioFile.eof()) {
        // 4. Đọc một khối dữ liệu cố định
        audioFile.read(buffer, CHUNK_SIZE);

        // 5. Xử lý trường hợp khối cuối cùng (nhỏ hơn 4096 bytes)
        // gcount() trả về số byte thực tế vừa đọc được
        std::streamsize bytesRead = audioFile.gcount();

        if (bytesRead > 0) {
            totalBytesRead += bytesRead;
            
            // Giả lập gửi dữ liệu đến phần cứng âm thanh
            // std::cout << "Dang phat " << bytesRead << " bytes du lieu..." << std::endl;
        }

        if (bytesRead < CHUNK_SIZE) {
            std::cout << "--- Da doc den cuoi file (End of File) ---" << std::endl;
            break;
        }
    }

    std::cout << "Tong so byte du lieu am thanh da xu ly: " << totalBytesRead << " bytes." << std::endl;
    audioFile.close();
}

int main() {
    const char* dummyFile = "test_audio.wav";

    // --- Tao file gia lap 1MB de test ---
    std::ofstream out(dummyFile, std::ios::binary);
    std::vector<char> dummyData(1024 * 1024, 0); // 1MB du lieu trang
    out.write(dummyData.data(), dummyData.size());
    out.close();

    // --- Chay ham mo phong ---
    playAudioFile(dummyFile);

    return 0;
}