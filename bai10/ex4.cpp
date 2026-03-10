//lưu lại file khi xảy ra bất ngờ
#include <iostream>
#include <fstream>
#include <cstdio>   // Cho hàm rename() và remove()
#include <string>

bool safeSave(const std::string& data, const std::string& filename) {
    std::string tempFilename = filename + ".tmp";

    // BƯỚC 1: Ghi vào file tạm
    std::ofstream outFile(tempFilename);
    if (!outFile.is_open()) {
        std::cerr << "Loi: Khong the tao file tam!" << std::endl;
        return false;
    }

    outFile << data;
    
    // BƯỚC 2: Kiểm tra lỗi sau khi ghi
    if (outFile.fail()) {
        outFile.close();
        std::remove(tempFilename.c_str()); // Xóa file tạm bị lỗi
        std::cerr << "Loi: Ghi du lieu vao file tam that bai!" << std::endl;
        return false;
    }
    outFile.close();

    // BƯỚC 3: Đổi tên file tạm thành file gốc (Atomic Rename)
    // Nếu rename thành công, file gốc cũ sẽ bị thay thế hoàn toàn bởi file tạm
    if (std::rename(tempFilename.c_str(), filename.c_str()) == 0) {
        std::cout << "Luu file an toan thanh cong!" << std::endl;
        return true;
    } else {
        std::cerr << "Loi: Khong the ghi de file goc!" << std::endl;
        std::remove(tempFilename.c_str());
        return false;
    }
}

int main() {
    std::string playlistData = "Song 1, Song 2, Song 3";
    std::string targetFile = "playlist.txt";

    if (safeSave(playlistData, targetFile)) {
        std::cout << "Du lieu da duoc bao ve an toan." << std::endl;
    }
    return 0;
}