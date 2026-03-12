#include <iostream>
#include <string>

using namespace std;

// 1. Lớp cơ sở cao nhất
class MediaObject {
public:
    MediaObject() {
        cout << "1. MediaObject Constructor (Cap phat Metadata)\n";
    }
    // QUAN TRỌNG: Destructor phải là virtual
    virtual ~MediaObject() {
        cout << "4. MediaObject Destructor (Giai phong Metadata)\n";
    }
};

// 2. Lớp kế thừa từ MediaObject
class AudioTrack : public MediaObject {
public:
    AudioTrack() {
        cout << "2. AudioTrack Constructor (Mo file am thanh)\n";
    }
    ~AudioTrack() override {
        cout << "3. AudioTrack Destructor (Dong file am thanh)\n";
    }
};

// 3. Lớp kế thừa từ AudioTrack
class LosslessAudioTrack : public AudioTrack {
public:
    LosslessAudioTrack() {
        cout << "3. LosslessAudioTrack Constructor (Khoi tao bo giai ma Lossless)\n";
    }
    ~LosslessAudioTrack() override {
        cout << "2. LosslessAudioTrack Destructor (Huy bo giai ma Lossless)\n";
    }
};

// 4. Lớp dẫn xuất cuối cùng
class FLACFile : public LosslessAudioTrack {
public:
    FLACFile() {
        cout << "4. FLACFile Constructor (Doc cau truc file .flac)\n";
    }
    ~FLACFile() override {
        cout << "1. FLACFile Destructor (Giai phong bo nho tam FLAC)\n";
    }
};

// --- CHƯƠNG TRÌNH THỬ NGHIỆM ---

void testStaticObject() {
    cout << "--- Khoi tao doi tuong Tinh (Stack) ---\n";
    {
        FLACFile myFile; 
        // Khi het ngoac nhon nay, myFile se bi huy
    }
    cout << "--- Doi tuong Tinh da bi huy ---\n\n";
}

void testDynamicObject() {
    cout << "--- Khoi tao doi tuong Dong (Heap) qua con tro lop cha ---\n";
    MediaObject* ptr = new FLACFile();
    
    cout << "\nDang thuc hien lenh 'delete ptr'...\n";
    delete ptr; // Nho co virtual destructor, moi thu se duoc don dep sach se
    cout << "--- Ket thuc test doi tuong Dong ---\n";
}

int main() {
    testStaticObject();
    testDynamicObject();
    return 0;
}