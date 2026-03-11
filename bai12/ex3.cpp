#include <iostream>
#include <string>

// 1. Decoder Interface (Sản phẩm trừu tượng)
class AudioDecoder {
public:
    virtual ~AudioDecoder() {}
    virtual void decode() = 0; // Đơn giản hóa hàm decodeChunk từ đề bài
};

// Các Concrete Decoders (Sản phẩm cụ thể)
class MP3Decoder : public AudioDecoder {
public:
    void decode() override { std::cout << "Dang giai ma du lieu MP3...\n"; }
};

class FLACDecoder : public AudioDecoder {
public:
    void decode() override { std::cout << "Dang giai ma du lieu FLAC (Lossless)...\n"; }
};

// 2. Factory Interface (Nhà máy trừu tượng)
class DecoderFactory {
public:
    virtual ~DecoderFactory() {}
    virtual AudioDecoder* createDecoder() = 0;
};

// 3. Concrete Factories (Các nhà máy cụ thể)
class MP3DecoderFactory : public DecoderFactory {
public:
    AudioDecoder* createDecoder() override {
        return new MP3Decoder();
    }
};

class FLACDecoderFactory : public DecoderFactory {
public:
    AudioDecoder* createDecoder() override {
        return new FLACDecoder();
    }
};

// 4. Sử dụng Factory (Ứng dụng chính)
int main() {
    DecoderFactory* factory = nullptr;
    AudioDecoder* decoder = nullptr;

    // Giả sử hệ thống phát hiện đây là file FLAC
    std::cout << "He thong: Phat hien dinh dang FLAC.\n";
    factory = new FLACDecoderFactory(); // Cấu hình nhà máy cụ thể

    // Tạo bộ giải mã mà không cần biết nó là lớp nào cụ thể
    decoder = factory->createDecoder(); 
    decoder->decode();

    // Dọn dẹp
    delete decoder;
    delete factory;

    return 0;
}