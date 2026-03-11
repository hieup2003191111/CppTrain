#include <iostream>
#include <string>

class Track {
private:
    std::string path;
    std::string title;
    int duration;

public:
    // 1. HÀM DỰNG "CHỦ" (Master Constructor)
    // Sử dụng Member Initializer List để khởi tạo giá trị
    Track(std::string p, std::string t, int d) 
        : path(p), title(t), duration(d) {
        
        // Thực hiện logic chung phức tạp ở đây
        std::cout << "[Logic Chung] Dang kiem tra file tai: " << path << std::endl;
        if (path.empty()) {
            this->path = "default.mp3";
        }
    }

    // 2. ỦY QUYỀN HÀM DỰNG (Constructor Delegation)
    
    // Chỉ có path -> gọi Master với title mặc định và duration = 0
    Track(std::string p) : Track(p, "Unknown Title", 0) {
        std::cout << "Goi ham dung 1 tham so" << std::endl;
    }

    // Có path và title -> gọi Master với duration = 0
    Track(std::string p, std::string t) : Track(p, t, 0) {
        std::cout << "Goi ham dung 2 tham so" << std::endl;
    }

    void display() const {
        std::cout << "Track: " << title << " [" << duration << "s] at " << path << "\n" << std::endl;
    }
};

int main() {
    Track t1("/music/song1.mp3");
    Track t2("/music/song2.mp3", "Hello World");
    Track t3("/music/song3.mp3", "Master Track", 180);
    Track t4("", "avater", 180);


    t1.display();
    t2.display();
    t3.display();
    t4.display();

    return 0;
}