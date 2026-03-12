#include <iostream>

class AudioEffect {
public:
    AudioEffect() { std::cout << "AudioEffect constructed\n"; }
    // THIẾU VIRTUAL Ở ĐÂY
    virtual ~AudioEffect() { std::cout << "AudioEffect destroyed\n"; }
};

class ReverbEffect : public AudioEffect {
public:
    ReverbEffect() { std::cout << "Reverb buffers allocated\n"; }
    ~ReverbEffect() override { std::cout << "Reverb buffers freed\n"; }
};

int main() {
    AudioEffect* effect = new ReverbEffect();
    delete effect; 
    return 0;
}
//giải thích
//khi không có virtual,C++ hiểu đó là liên kết tĩnh,nó sẽ chỉ đọc đến Lớp cha,không đọc xuống lớp con.
