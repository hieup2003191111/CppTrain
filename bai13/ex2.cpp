#include <iostream>

class GenericAudioSource {
public:
    virtual void connect() {
        std::cout << "Dang thuc hien ket noi chung...\n";
    }
    virtual ~GenericAudioSource() {}
};

class BluetoothSource : public GenericAudioSource {
private:
    // YÊU CẦU 1: Ghi đè và chuyển thành private
    void connect() override {
        std::cout << "[Bluetooth] Dang thuc hien ket noi phuc tap sau khi ghep doi.\n";
    }

public:
    void pairAndConnect() {
        std::cout << "[Bluetooth] Bat dau qua trinh ghep doi an toan...\n";
        // Vẫn gọi được vì connect() là thành viên của chính lớp này
        connect(); 
    }
};

int main() {
    BluetoothSource* bt = new BluetoothSource();

    bt->pairAndConnect(); // OK - In ra log ghép đôi và kết nối

     //bt->connect();     
    // LỖI BIÊN DỊCH: 'virtual void BluetoothSource::connect()' is private within this context

    delete bt;
    return 0;
}