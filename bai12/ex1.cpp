#include <iostream>  
#include <vector>  
#include <string>  
#include <windows.h> 
using namespace std;
class AudioSource{
public:
    virtual ~AudioSource(){};
    virtual bool open(const char* source_path) = 0; 
    virtual size_t read(char* buffer, size_t bytes_to_read) = 0; 
    virtual bool seek(long offset) = 0; 
    virtual void close() = 0;
};
//lớp abstract base có tác dụng định nghĩa cơ bản các phương thức cho các lớp kế thừa nó
class LocalFileSource : public AudioSource {
private:
    FILE* filePtr = nullptr;

public:
    bool open(const char* source_path) override {
        filePtr = fopen(source_path, "rb");
        return filePtr != nullptr;
    }

    size_t read(char* buffer, size_t bytes_to_read) override {
        if (!filePtr) return 0;
        return fread(buffer, 1, bytes_to_read, filePtr);
    }

    bool seek(long offset) override {
        if (!filePtr) return false;
        return fseek(filePtr, offset, SEEK_SET) == 0;
    }

    void close() override {
        if (filePtr) {
            fclose(filePtr);
            filePtr = nullptr;
        }
    }

    ~LocalFileSource() { close(); }
};
// Giả sử ta có thêm một lớp Bluetooth nữa để so sánh
class BluetoothAudioSource : public AudioSource {
public:
    bool open(const char* path) override {
        std::cout << "[Bluetooth] Dang ket noi toi thiet bi: " << path << std::endl;
        return true; 
    }
    size_t read(char* buffer, size_t size) override { return size; } // Giả lập
    bool seek(long offset) override { return true; }
    void close() override { std::cout << "[Bluetooth] Ngat ket noi.\n"; }
    ~BluetoothAudioSource(){close();};
};
void PlayerEngine(AudioSource* currentSource, const char* sourcePath) {
    std::cout << "\n--- Player Engine bat dau lam viec ---" << std::endl;
    
    // Engine không cần biết currentSource là File hay Bluetooth!
    // Nó chỉ gọi các hàm mà lớp cha AudioSource đã hứa là sẽ có.
    if (currentSource->open(sourcePath)) {
        char buffer[1024];
        currentSource->read(buffer, 1024);
        currentSource->seek(500);
        currentSource->close();
    }
    
    std::cout << "--- Player Engine hoan tat ---\n" << std::endl;
}
int main() {
    // Bước 1: Tạo các nguồn âm thanh khác nhau
    AudioSource* file = new LocalFileSource();
    AudioSource* bluetooth = new BluetoothAudioSource();

    // Bước 2: Dùng chung 1 hàm PlayerEngine cho cả 2 loại
    // Đây là đa hình!
    PlayerEngine(file, "nhac_tre.mp3");
    PlayerEngine(bluetooth, "AirPods_Pro_01");

    // Dọn dẹp
    delete file;
    delete bluetooth;

    return 0;
}

