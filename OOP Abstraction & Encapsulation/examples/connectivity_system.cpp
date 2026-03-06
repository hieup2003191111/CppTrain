#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Lớp trừu tượng cho phương tiện giao tiếp
class CommunicationDevice {
public:
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual bool sendData(const std::string& data) = 0;
    virtual std::string receiveData() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string getDeviceInfo() const = 0;
    virtual ~CommunicationDevice() {}
};

// Lớp cụ thể: Bluetooth
class BluetoothDevice : public CommunicationDevice {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    std::string deviceName;
    std::string deviceAddress;
    bool connected;
    int signalStrength;  // 0-100
    std::vector<std::string> pairedDevices;
    
    // Phương thức private
    bool authenticateConnection(const std::string& pin) {
        // Mô phỏng xác thực kết nối Bluetooth
        // Trong thực tế, đây sẽ là giao thức xác thực thật
        return pin == "1234"; // PIN mặc định
    }

public:
    BluetoothDevice(const std::string& name, const std::string& address)
        : deviceName(name), deviceAddress(address), connected(false), signalStrength(0) {}
    
    bool connect() override {
        if (!connected) {
            // Mô phỏng kết nối
            std::cout << "Attempting to connect to Bluetooth device: " << deviceName << std::endl;
            
            // Giả lập xác thực
            bool authenticated = authenticateConnection("1234");
            
            if (authenticated) {
                connected = true;
                signalStrength = 80 + rand() % 20; // Giả lập cường độ tín hiệu từ 80-99
                std::cout << "Connected to " << deviceName << " with signal strength: " 
                          << signalStrength << "%" << std::endl;
                return true;
            } else {
                std::cout << "Authentication failed for " << deviceName << std::endl;
                return false;
            }
        }
        
        std::cout << "Already connected to " << deviceName << std::endl;
        return true;
    }
    
    void disconnect() override {
        if (connected) {
            connected = false;
            signalStrength = 0;
            std::cout << "Disconnected from " << deviceName << std::endl;
        }
    }
    
    bool sendData(const std::string& data) override {
        if (!connected) {
            std::cout << "Cannot send data: Not connected to " << deviceName << std::endl;
            return false;
        }
        
        std::cout << "Sending data to " << deviceName << ": " << data << std::endl;
        return true;
    }
    
    std::string receiveData() override {
        if (!connected) {
            return "";
        }
        
        // Giả lập nhận dữ liệu
        return "ACK from " + deviceName;
    }
    
    bool isConnected() const override {
        return connected;
    }
    
    std::string getDeviceInfo() const override {
        std::string info = "Bluetooth Device: " + deviceName + "\n";
        info += "Address: " + deviceAddress + "\n";
        info += "Status: " + std::string(connected ? "Connected" : "Disconnected") + "\n";
        
        if (connected) {
            info += "Signal Strength: " + std::to_string(signalStrength) + "%\n";
        }
        
        return info;
    }
    
    // Các phương thức bổ sung đặc thù cho Bluetooth
    void addPairedDevice(const std::string& deviceName) {
        if (std::find(pairedDevices.begin(), pairedDevices.end(), deviceName) == pairedDevices.end()) {
            pairedDevices.push_back(deviceName);
            std::cout << deviceName << " added to paired devices list" << std::endl;
        }
    }
    
    void removePairedDevice(const std::string& deviceName) {
        auto it = std::find(pairedDevices.begin(), pairedDevices.end(), deviceName);
        if (it != pairedDevices.end()) {
            pairedDevices.erase(it);
            std::cout << deviceName << " removed from paired devices list" << std::endl;
        }
    }
    
    std::vector<std::string> getPairedDevices() const {
        return pairedDevices;
    }
};

// Lớp cụ thể: WiFi
class WiFiDevice : public CommunicationDevice {
private:
    std::string ssid;
    std::string password;
    std::string ipAddress;
    bool connected;
    int signalStrength; // 0-100
    bool isSecureNetwork;

public:
    WiFiDevice(const std::string& networkName, const std::string& pwd, bool secure = true)
        : ssid(networkName), password(pwd), connected(false), 
          signalStrength(0), isSecureNetwork(secure) {}
    
    bool connect() override {
        if (!connected) {
            std::cout << "Attempting to connect to WiFi network: " << ssid << std::endl;
            
            // Giả lập kết nối thành công nếu có mật khẩu hoặc mạng không bảo mật
            bool connectionSuccess = !isSecureNetwork || !password.empty();
            
            if (connectionSuccess) {
                connected = true;
                signalStrength = 60 + rand() % 40; // 60-99%
                
                // Giả lập gán địa chỉ IP
                ipAddress = "192.168.1." + std::to_string(100 + rand() % 100);
                
                std::cout << "Connected to " << ssid << " with IP: " << ipAddress 
                          << ", signal: " << signalStrength << "%" << std::endl;
                return true;
            } else {
                std::cout << "Failed to connect to " << ssid << std::endl;
                return false;
            }
        }
        
        std::cout << "Already connected to " << ssid << std::endl;
        return true;
    }
    
    void disconnect() override {
        if (connected) {
            connected = false;
            signalStrength = 0;
            ipAddress = "";
            std::cout << "Disconnected from WiFi network: " << ssid << std::endl;
        }
    }
    
    bool sendData(const std::string& data) override {
        if (!connected) {
            std::cout << "Cannot send data: Not connected to WiFi" << std::endl;
            return false;
        }
        
        std::cout << "Sending data over WiFi (" << ssid << "): " << data << std::endl;
        return true;
    }
    
    std::string receiveData() override {
        if (!connected) {
            return "";
        }
        
        // Giả lập nhận dữ liệu
        return "Data received over WiFi from " + ssid;
    }
    
    bool isConnected() const override {
        return connected;
    }
    
    std::string getDeviceInfo() const override {
        std::string info = "WiFi Device:\n";
        info += "SSID: " + ssid + "\n";
        info += "Security: " + std::string(isSecureNetwork ? "Enabled" : "Disabled") + "\n";
        info += "Status: " + std::string(connected ? "Connected" : "Disconnected") + "\n";
        
        if (connected) {
            info += "IP Address: " + ipAddress + "\n";
            info += "Signal Strength: " + std::to_string(signalStrength) + "%\n";
        }
        
        return info;
    }
    
    // Các phương thức bổ sung đặc thù cho WiFi
    std::string getIPAddress() const {
        return ipAddress;
    }
    
    void scanNetworks() {
        std::cout << "Scanning for WiFi networks..." << std::endl;
        
        // Giả lập quét mạng
        std::vector<std::string> networks = {"Home_WiFi", "Office_Network", "Guest_WiFi", "Public_Hotspot"};
        
        for (const auto& network : networks) {
            int strength = 30 + rand() % 70;
            std::cout << "  * " << network << " (Signal: " << strength << "%)" << std::endl;
        }
    }
};

// Lớp quản lý kết nối
class ConnectivityManager {
private:
    std::vector<CommunicationDevice*> devices;
    CommunicationDevice* activeDevice;

public:
    ConnectivityManager() : activeDevice(nullptr) {}
    
    void addDevice(CommunicationDevice* device) {
        devices.push_back(device);
        std::cout << "Device added to connectivity manager" << std::endl;
    }
    
    bool connectToDevice(int index) {
        if (index >= 0 && index < static_cast<int>(devices.size())) {
            CommunicationDevice* device = devices[index];
            
            if (device->connect()) {
                activeDevice = device;
                return true;
            }
        }
        return false;
    }
    
    void disconnectActiveDevice() {
        if (activeDevice && activeDevice->isConnected()) {
            activeDevice->disconnect();
        }
    }
    
    void disconnectAllDevices() {
        for (auto device : devices) {
            if (device->isConnected()) {
                device->disconnect();
            }
        }
        activeDevice = nullptr;
    }
    
    bool sendMessage(const std::string& message) {
        if (activeDevice && activeDevice->isConnected()) {
            return activeDevice->sendData(message);
        }
        
        std::cout << "No active connected device to send message" << std::endl;
        return false;
    }
    
    void listAllDevices() {
        std::cout << "\n===== CONNECTIVITY DEVICES =====" << std::endl;
        for (size_t i = 0; i < devices.size(); ++i) {
            std::cout << i << ". " << devices[i]->getDeviceInfo() << std::endl;
        }
    }
    
    // Giải phóng bộ nhớ khi hủy đối tượng
    ~ConnectivityManager() {
        for (auto device : devices) {
            delete device;
        }
    }
};

// Hàm main để kiểm thử
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Tạo các thiết bị liên lạc
    BluetoothDevice* phone = new BluetoothDevice("Samsung Galaxy", "00:11:22:33:44:55");
    BluetoothDevice* headset = new BluetoothDevice("Sony Headphones", "AA:BB:CC:DD:EE:FF");
    WiFiDevice* homeWifi = new WiFiDevice("Home_Network", "securepassword", true);
    
    // Tạo quản lý kết nối
    ConnectivityManager manager;
    
    // Thêm các thiết bị
    manager.addDevice(phone);
    manager.addDevice(headset);
    manager.addDevice(homeWifi);
    
    // Liệt kê thiết bị
    manager.listAllDevices();
    
    // Kết nối với điện thoại
    std::cout << "\n===== CONNECTING TO PHONE =====" << std::endl;
    if (manager.connectToDevice(0)) {
        // Thêm thiết bị đã ghép nối với điện thoại
        phone->addPairedDevice("Sony Headphones");
        phone->addPairedDevice("Car Audio System");
        
        // Gửi tin nhắn
        manager.sendMessage("Hello from car infotainment system!");
    }
    
    // Kết nối với WiFi
    std::cout << "\n===== CONNECTING TO WIFI =====" << std::endl;
    manager.disconnectActiveDevice();
    
    if (manager.connectToDevice(2)) {
        // Quét mạng WiFi
        dynamic_cast<WiFiDevice*>(homeWifi)->scanNetworks();
        
        // Gửi tin nhắn
        manager.sendMessage("Updating map data over WiFi...");
    }
    
    // Liệt kê lại thiết bị sau khi sử dụng
    manager.listAllDevices();
    
    // Ngắt kết nối tất cả
    manager.disconnectAllDevices();
    
    return 0;
}
