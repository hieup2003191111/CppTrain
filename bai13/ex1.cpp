#include <iostream>

class DigitalAsset {
public:
    long licenseID;
    // Constructor của lớp gốc
    DigitalAsset(long id) : licenseID(id) {
        std::cout << "[DigitalAsset] Khoi tao ID: " << licenseID << std::endl;
    }
};

// Sử dụng virtual inheritance
class AudioContent : virtual public DigitalAsset {
public:
    int bitrate;
    // Gọi constructor cha như bình thường
    AudioContent(long id, int br) : DigitalAsset(id), bitrate(br) {}
};

class Playable : virtual public DigitalAsset {
public:
    int duration;
    // Gọi constructor cha như bình thường
    Playable(long id, int dur) : DigitalAsset(id), duration(dur) {}
};

// Lớp dẫn xuất cuối cùng - ĐÂY LÀ NƠI QUAN TRỌNG NHẤT
class PlayableSong : public AudioContent, public Playable {
public:
    // QUY TẮC: Phải gọi trực tiếp DigitalAsset(id) ở đây!
    PlayableSong(long id, int br, int dur) 
        : DigitalAsset(id), AudioContent(id, br), Playable(id, dur) 
    {
        std::cout << "[PlayableSong] Khoi tao xong bai hat." << std::endl;
    }
};

int main() {
    PlayableSong mySong(999, 320, 240);
    std::cout << "ID bai hat: " << mySong.licenseID << std::endl;
    return 0;
}

//giải quyết vấn đế đa kế thừa,đảm bảo chỉ tồn tại 1 instance