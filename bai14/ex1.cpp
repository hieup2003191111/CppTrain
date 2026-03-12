#include <iostream>
#include <vector>
#include <string>

// --- YÊU CẦU 1: THIẾT KẾ LỚP ---

// Lớp cơ sở AudioSource
class AudioSource {
public:
    // 1. Phải có ít nhất một hàm ảo để kích hoạt RTTI (Run-Time Type Information)
    // getSourceType() = 0 biến đây thành một lớp trừu tượng (Abstract Class)
    virtual const char* getSourceType() = 0;

    // 2. Virtual destructor: Luôn cần thiết để giải phóng bộ nhớ lớp con an toàn
    virtual ~AudioSource() {
        std::cout << "Huy AudioSource" << std::endl;
    }
};

// Lớp dẫn xuất LocalFileSource (Nguồn nhạc từ file máy tính)
class LocalFileSource : public AudioSource {
public:
    const char* getSourceType() override {
        return "Local File Source";
    }
    
    ~LocalFileSource() override {
        std::cout << "Huy LocalFileSource" << std::endl;
    }
};

// Lớp dẫn xuất InternetRadioSource (Nguồn nhạc từ Radio Online)
class InternetRadioSource : public AudioSource {
public:
    const char* getSourceType() override {
        return "Internet Radio Source";
    }

    // 3. Phương thức đặc thù (Unique method) - Chỉ lớp này mới có
    void displayMetadata() {
        std::cout << ">>> [METADATA]: Station: Rock FM | Song: Highway to Hell | Bitrate: 320kbps" << std::endl;
    }

    ~InternetRadioSource() override {
        std::cout << "Huy InternetRadioSource" << std::endl;
    }
};

int main() {
    // 1. Tạo danh sách các nguồn âm thanh (quản lý bằng con trỏ lớp cha)
    std::vector<AudioSource*> playlist;

    playlist.push_back(new LocalFileSource());
    playlist.push_back(new InternetRadioSource());
    playlist.push_back(new LocalFileSource());
    playlist.push_back(new InternetRadioSource());

    std::cout << "--- DUYET DANH SACH AM THANH (Dung dynamic_cast) ---\n" << std::endl;

    // 2. Viết vòng lặp duyệt qua vector
    for (AudioSource* source : playlist) {
        std::cout << "Dang kiem tra: " << source->getSourceType() << std::endl;

        // 3. Sử dụng dynamic_cast để kiểm tra kiểu thực tế của đối tượng tại thời điểm chạy (Runtime)
        // Cú pháp: dynamic_cast<Kieu_Dich*>(Ten_Bien_Con_Tro)
        InternetRadioSource* radioPtr = dynamic_cast<InternetRadioSource*>(source);

        // 4. Kiểm tra kết quả ép kiểu
        if (radioPtr != nullptr) {
            // Nếu thành công (không phải nullptr), nghĩa là đối tượng này thực sự là InternetRadioSource
            std::cout << "  => Phat hien nguon Internet Radio! Dang truy cap tinh nang rieng..." << std::endl;
            radioPtr->displayMetadata(); // Gọi phương thức đặc thù an toàn
        } else {
            // Nếu trả về nullptr, nghĩa là đối tượng là kiểu khác (ví dụ: LocalFileSource)
            std::cout << "  => Nguon nay khong phai Internet Radio. Bo qua displayMetadata()." << std::endl;
        }
        std::cout << "------------------------------------------" << std::endl;
    }

    // 5. Giải phóng bộ nhớ
    for (AudioSource* s : playlist) {
        delete s;
    }
    playlist.clear();

    return 0;
}