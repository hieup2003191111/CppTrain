# Hệ thống thông tin giải trí (Infotainment System) sử dụng Abstraction và Encapsulation

Hệ thống thông tin giải trí trong ô tô hiện đại là giao diện chính giữa người dùng và nhiều hệ thống của xe. Việc áp dụng nguyên tắc Abstraction và Encapsulation trong thiết kế phần mềm infotainment giúp tạo ra hệ thống linh hoạt, bảo mật và dễ sử dụng.

## 1. Kiến trúc phần mềm Infotainment

### Các thành phần chính
- **Giao diện người dùng (UI Layer)**
- **Quản lý đa phương tiện (Media Management)**
- **Điều hướng và GPS (Navigation)**
- **Kết nối điện thoại (Phone Connectivity)**
- **Điều khiển hệ thống xe (Vehicle System Controls)**

### Mô hình lớp trừu tượng

```
           ┌───────────────────┐
           │ MediaPlayer       │
           │    (Abstract)     │
           └────────┬──────────┘
                    │
      ┌─────────────┼─────────────┐
      │             │             │
┌─────▼────┐  ┌─────▼────┐  ┌─────▼────┐
│AudioPlayer│  │VideoPlayer│  │ImageViewer│
└──────────┘  └──────────┘  └──────────┘
```

## 2. Ứng dụng Abstraction

### Ví dụ: Hệ thống media player

```cpp
// Lớp trừu tượng cho Media Player
class MediaPlayer {
public:
    // Phương thức thuần ảo
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void seekTo(int position) = 0;
    virtual bool loadMedia(const std::string& path) = 0;
    virtual MediaInfo getMediaInfo() const = 0;
    
    // Destructor ảo
    virtual ~MediaPlayer() {}
    
protected:
    // Các phương thức và thuộc tính chung
    void notifyPlaybackStatus(PlaybackStatus status) {
        // Thông báo trạng thái phát
    }
    
    MediaInfo mediaInfo;
};

// Lớp cụ thể: Audio Player
class AudioPlayer : public MediaPlayer {
public:
    void play() override {
        if (audioDecoder && audioDecoder->isReady()) {
            audioDecoder->startPlayback();
            notifyPlaybackStatus(PlaybackStatus::Playing);
        }
    }
    
    void pause() override {
        if (audioDecoder && audioDecoder->isPlaying()) {
            audioDecoder->pausePlayback();
            notifyPlaybackStatus(PlaybackStatus::Paused);
        }
    }
    
    void stop() override {
        if (audioDecoder) {
            audioDecoder->stopPlayback();
            notifyPlaybackStatus(PlaybackStatus::Stopped);
        }
    }
    
    void seekTo(int position) override {
        if (audioDecoder) {
            audioDecoder->seekToPosition(position);
        }
    }
    
    bool loadMedia(const std::string& path) override {
        // Giải phóng bộ giải mã hiện tại nếu có
        if (audioDecoder) {
            delete audioDecoder;
        }
        
        // Tạo bộ giải mã thích hợp dựa trên định dạng tệp
        std::string extension = getFileExtension(path);
        
        if (extension == "mp3") {
            audioDecoder = new MP3Decoder();
        } 
        else if (extension == "aac") {
            audioDecoder = new AACDecoder();
        }
        else if (extension == "flac") {
            audioDecoder = new FLACDecoder();
        }
        else {
            return false;  // Không hỗ trợ định dạng
        }
        
        // Tải tệp âm thanh
        bool success = audioDecoder->loadFile(path);
        
        if (success) {
            // Cập nhật thông tin media
            mediaInfo.duration = audioDecoder->getDuration();
            mediaInfo.title = extractFileName(path);
            mediaInfo.type = MediaType::Audio;
            
            // Thêm thông tin từ metadata
            audioDecoder->extractMetadata(&mediaInfo);
        }
        
        return success;
    }
    
    MediaInfo getMediaInfo() const override {
        return mediaInfo;
    }
    
    // Phương thức đặc thù cho audio
    void setEqualizerSettings(const EqualizerSettings& settings) {
        if (audioDecoder) {
            audioDecoder->applyEqualizer(settings);
        }
    }

private:
    AudioDecoder* audioDecoder = nullptr;
    
    std::string getFileExtension(const std::string& path) {
        // Trích xuất phần mở rộng tệp
        size_t dotPos = path.find_last_of(".");
        if (dotPos != std::string::npos) {
            return path.substr(dotPos + 1);
        }
        return "";
    }
    
    std::string extractFileName(const std::string& path) {
        // Trích xuất tên tệp từ đường dẫn
        size_t slashPos = path.find_last_of("/\\");
        if (slashPos != std::string::npos) {
            return path.substr(slashPos + 1);
        }
        return path;
    }
};

// Lớp cụ thể: Video Player
class VideoPlayer : public MediaPlayer {
    // Triển khai tương tự AudioPlayer nhưng với xử lý video
    // ...
};
```

### Lợi ích của Abstraction trong Infotainment
1. **Khả năng mở rộng**: Dễ dàng thêm hỗ trợ cho các định dạng media mới
2. **Tái sử dụng mã**: Cùng một giao diện điều khiển cho nhiều loại media
3. **Đơn giản hóa giao diện người dùng**: Ẩn đi các chi tiết phức tạp về xử lý media

## 3. Ứng dụng Encapsulation

### Ví dụ: Hệ thống Bluetooth

```cpp
class BluetoothSystem {
private:
    // Dữ liệu được bảo vệ
    bool isEnabled;
    bool isDiscoverable;
    bool isConnected;
    std::vector<BluetoothDevice> pairedDevices;
    BluetoothDevice* connectedDevice;
    
    // Thuật toán và xử lý nội bộ
    bool authenticateDevice(const BluetoothDevice& device, const std::string& pin) {
        // Xác thực thiết bị
        return device.verifyPIN(pin);
    }
    
    void updateDeviceStatus() {
        // Cập nhật trạng thái thiết bị
        isConnected = (connectedDevice != nullptr);
    }

public:
    // Constructor
    BluetoothSystem() 
        : isEnabled(false), isDiscoverable(false), 
          isConnected(false), connectedDevice(nullptr) {}
    
    // Getters - Chỉ đọc thông tin
    bool getIsEnabled() const { return isEnabled; }
    bool getIsDiscoverable() const { return isDiscoverable; }
    bool getIsConnected() const { return isConnected; }
    std::vector<BluetoothDevice> getPairedDevices() const { return pairedDevices; }
    BluetoothDevice* getConnectedDevice() const { return connectedDevice; }
    
    // Chức năng công khai
    bool enable() {
        if (!isEnabled) {
            // Khởi tạo phần cứng Bluetooth
            bool hardwareInitialized = initializeHardware();
            if (hardwareInitialized) {
                isEnabled = true;
                return true;
            }
        }
        return false;
    }
    
    void disable() {
        if (isEnabled) {
            // Ngắt kết nối thiết bị hiện tại nếu có
            if (isConnected) {
                disconnectDevice();
            }
            
            // Tắt Bluetooth
            shutdownHardware();
            isEnabled = false;
            isDiscoverable = false;
        }
    }
    
    void setDiscoverable(bool discoverable, int timeoutSeconds = 120) {
        if (isEnabled) {
            isDiscoverable = discoverable;
            if (discoverable) {
                // Bắt đầu tính thời gian hết hạn
                startDiscoverabilityTimeout(timeoutSeconds);
            }
        }
    }
    
    std::vector<BluetoothDevice> scanForDevices(int timeoutSeconds = 10) {
        if (!isEnabled) {
            return {};
        }
        
        // Quét thiết bị gần đó
        return performDeviceScan(timeoutSeconds);
    }
    
    bool pairDevice(const BluetoothDevice& device, const std::string& pin) {
        if (!isEnabled) {
            return false;
        }
        
        // Xác thực thiết bị
        if (authenticateDevice(device, pin)) {
            // Thêm vào danh sách thiết bị đã ghép nối
            pairedDevices.push_back(device);
            return true;
        }
        
        return false;
    }
    
    bool connectToDevice(const BluetoothDevice& device) {
        if (!isEnabled) {
            return false;
        }
        
        // Kiểm tra xem thiết bị đã được ghép nối chưa
        bool isPaired = false;
        for (const auto& paired : pairedDevices) {
            if (paired.getAddress() == device.getAddress()) {
                isPaired = true;
                break;
            }
        }
        
        if (!isPaired) {
            return false;
        }
        
        // Ngắt kết nối thiết bị hiện tại nếu có
        if (isConnected) {
            disconnectDevice();
        }
        
        // Kết nối với thiết bị mới
        bool connected = performConnect(device);
        if (connected) {
            connectedDevice = new BluetoothDevice(device);
            updateDeviceStatus();
        }
        
        return connected;
    }
    
    void disconnectDevice() {
        if (isConnected && connectedDevice) {
            performDisconnect(*connectedDevice);
            delete connectedDevice;
            connectedDevice = nullptr;
            updateDeviceStatus();
        }
    }

private:
    bool initializeHardware() {
        // Khởi tạo phần cứng Bluetooth
        return true;
    }
    
    void shutdownHardware() {
        // Tắt phần cứng Bluetooth
    }
    
    void startDiscoverabilityTimeout(int seconds) {
        // Bắt đầu hẹn giờ tắt tính năng phát hiện
    }
    
    std::vector<BluetoothDevice> performDeviceScan(int timeoutSeconds) {
        // Thực hiện quét thiết bị
        std::vector<BluetoothDevice> devices;
        // ...
        return devices;
    }
    
    bool performConnect(const BluetoothDevice& device) {
        // Thực hiện kết nối với thiết bị
        return true;
    }
    
    void performDisconnect(const BluetoothDevice& device) {
        // Ngắt kết nối với thiết bị
    }
};
```

### Lợi ích của Encapsulation trong Infotainment
1. **Bảo mật dữ liệu**: Bảo vệ thông tin kết nối và ghép nối Bluetooth
2. **Quản lý trạng thái**: Đảm bảo hệ thống luôn ở trạng thái nhất quán
3. **API đơn giản**: Cung cấp giao diện đơn giản để tương tác với hệ thống phức tạp
4. **Kiểm soát lỗi**: Xử lý lỗi bên trong lớp mà không làm ảnh hưởng đến người dùng

## 4. Thiết kế hệ thống thông tin giải trí toàn diện

### Ví dụ: Hệ thống Infotainment tích hợp

```cpp
// Lớp tích hợp tổng thể
class InfotainmentSystem {
private:
    // Các thành phần con - Encapsulation
    AudioSystem audioSystem;
    NavigationSystem navigationSystem;
    BluetoothSystem bluetoothSystem;
    ClimateControlInterface climateInterface;
    VehicleSettingsInterface vehicleSettings;
    
    // Trạng thái hệ thống
    bool isOn;
    ScreenMode currentScreenMode;
    int volumeLevel;
    
    // Quản lý cấu hình người dùng
    std::map<std::string, UserProfile> userProfiles;
    UserProfile* activeProfile;

public:
    // Constructor
    InfotainmentSystem()
        : isOn(false), currentScreenMode(ScreenMode::Home),
          volumeLevel(10), activeProfile(nullptr) {}
    
    // Power management
    void powerOn() {
        isOn = true;
        // Khởi động các hệ thống con
        bootSystem();
    }
    
    void powerOff() {
        isOn = false;
        // Tắt các hệ thống con an toàn
        shutdownSystem();
    }
    
    // Điều khiển âm thanh (delegation)
    void setVolume(int level) {
        if (level >= 0 && level <= MAX_VOLUME) {
            volumeLevel = level;
            audioSystem.setVolume(level);
        }
    }
    
    int getVolume() const {
        return volumeLevel;
    }
    
    // Chuyển đổi màn hình
    void switchToScreen(ScreenMode mode) {
        if (isOn) {
            currentScreenMode = mode;
            // Cập nhật giao diện người dùng
            updateUI();
        }
    }
    
    // Quản lý hồ sơ người dùng
    bool createUserProfile(const std::string& name) {
        if (userProfiles.find(name) == userProfiles.end()) {
            userProfiles[name] = UserProfile(name);
            return true;
        }
        return false;
    }
    
    bool switchToUserProfile(const std::string& name) {
        auto it = userProfiles.find(name);
        if (it != userProfiles.end()) {
            activeProfile = &(it->second);
            applyUserSettings();
            return true;
        }
        return false;
    }
    
    // Xử lý thông báo điện thoại
    void handlePhoneNotification(const PhoneNotification& notification) {
        if (isOn) {
            // Hiển thị thông báo trên màn hình
            displayNotification(notification);
            
            // Phát âm thanh thông báo qua hệ thống âm thanh
            if (notification.type == NotificationType::IncomingCall) {
                audioSystem.playRingtone();
            } else {
                audioSystem.playNotificationSound();
            }
        }
    }

private:
    const int MAX_VOLUME = 30;
    
    void bootSystem() {
        // Khởi động tuần tự các hệ thống con
        audioSystem.initialize();
        navigationSystem.initialize();
        bluetoothSystem.enable();
        
        // Khôi phục cài đặt người dùng gần đây nhất
        loadLastUserProfile();
        
        // Hiển thị màn hình chào
        showWelcomeScreen();
    }
    
    void shutdownSystem() {
        // Lưu cài đặt hiện tại
        saveCurrentSettings();
        
        // Tắt các hệ thống con
        bluetoothSystem.disable();
        navigationSystem.shutdown();
        audioSystem.shutdown();
    }
    
    void updateUI() {
        // Cập nhật giao diện người dùng dựa trên chế độ màn hình hiện tại
    }
    
    void loadLastUserProfile() {
        // Tải hồ sơ người dùng đã sử dụng gần đây nhất
        std::string lastUser = getLastUsedProfileName();
        if (!lastUser.empty()) {
            switchToUserProfile(lastUser);
        }
    }
    
    void applyUserSettings() {
        if (activeProfile) {
            // Áp dụng cài đặt của người dùng
            volumeLevel = activeProfile->getVolumePreference();
            audioSystem.setVolume(volumeLevel);
            audioSystem.setEqualizerSettings(activeProfile->getEqualizerSettings());
            
            // Áp dụng cài đặt điều hướng
            navigationSystem.setPreferredRouteType(activeProfile->getRoutePreference());
            
            // Áp dụng các cài đặt khác
            // ...
        }
    }
    
    std::string getLastUsedProfileName() {
        // Đọc từ bộ nhớ lâu dài
        return "DefaultUser"; // Giả định
    }
    
    void saveCurrentSettings() {
        // Lưu cài đặt hiện tại vào bộ nhớ lâu dài
    }
    
    void showWelcomeScreen() {
        // Hiển thị màn hình chào khi khởi động
        currentScreenMode = ScreenMode::Welcome;
        // Hiệu ứng đồ họa, âm thanh, v.v.
    }
    
    void displayNotification(const PhoneNotification& notification) {
        // Hiển thị thông báo trên giao diện người dùng
    }
};
```

## 5. Case Study: Apple CarPlay và Android Auto Integration

Tích hợp Apple CarPlay và Android Auto là ví dụ thực tế về việc sử dụng abstraction trong hệ thống infotainment hiện đại:

```cpp
// Lớp trừu tượng cho tích hợp smartphone
class SmartphoneIntegration {
public:
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual void displayHomeScreen() = 0;
    virtual void displayNavigation() = 0;
    virtual void displayMedia() = 0;
    virtual void sendCommand(const IntegrationCommand& cmd) = 0;
    virtual std::string getName() const = 0;
    virtual ~SmartphoneIntegration() {}
};

// Triển khai cụ thể cho Apple CarPlay
class AppleCarPlay : public SmartphoneIntegration {
private:
    bool connectionStatus;
    AppleAuthToken authToken;
    std::unique_ptr<CarPlayProtocol> protocol;
    
public:
    AppleCarPlay() : connectionStatus(false) {
        protocol = std::make_unique<CarPlayProtocol>();
    }
    
    bool connect() override {
        // Kết nối với iPhone qua USB hoặc Bluetooth
        connectionStatus = protocol->initializeConnection();
        if (connectionStatus) {
            authToken = protocol->authenticate();
            return true;
        }
        return false;
    }
    
    void disconnect() override {
        if (connectionStatus) {
            protocol->terminateConnection(authToken);
            connectionStatus = false;
        }
    }
    
    bool isConnected() const override {
        return connectionStatus;
    }
    
    void displayHomeScreen() override {
        if (connectionStatus) {
            protocol->requestScreen(CarPlayScreen::Home);
        }
    }
    
    void displayNavigation() override {
        if (connectionStatus) {
            protocol->requestScreen(CarPlayScreen::Maps);
        }
    }
    
    void displayMedia() override {
        if (connectionStatus) {
            protocol->requestScreen(CarPlayScreen::NowPlaying);
        }
    }
    
    void sendCommand(const IntegrationCommand& cmd) override {
        if (connectionStatus) {
            protocol->sendCommand(convertToCarPlayCommand(cmd));
        }
    }
    
    std::string getName() const override {
        return "Apple CarPlay";
    }
    
private:
    CarPlayCommand convertToCarPlayCommand(const IntegrationCommand& cmd) {
        // Chuyển đổi lệnh chung thành lệnh đặc thù cho CarPlay
        CarPlayCommand cpCmd;
        // Chuyển đổi...
        return cpCmd;
    }
};

// Triển khai cụ thể cho Android Auto
class AndroidAuto : public SmartphoneIntegration {
    // Triển khai tương tự như AppleCarPlay nhưng với giao thức Android Auto
    // ...
};

// Factory Method để tạo tích hợp phù hợp
class SmartphoneIntegrationFactory {
public:
    static std::unique_ptr<SmartphoneIntegration> 
    createIntegration(const ConnectedDevice& device) {
        if (device.getType() == DeviceType::iPhone) {
            return std::make_unique<AppleCarPlay>();
        } 
        else if (device.getType() == DeviceType::Android) {
            return std::make_unique<AndroidAuto>();
        }
        return nullptr;
    }
};
```

## 6. Kết luận

Việc áp dụng Abstraction và Encapsulation trong phát triển phần mềm hệ thống thông tin giải trí giúp:

1. **Tạo giao diện người dùng nhất quán**: Dù xử lý nhiều loại đa phương tiện và kết nối
2. **Dễ dàng tích hợp với công nghệ mới**: Thiết kế cởi mở cho phép tích hợp các hệ thống như CarPlay, Android Auto
3. **Bảo vệ dữ liệu người dùng**: Thông tin nhạy cảm như danh bạ được bảo vệ bằng encapsulation
4. **Quản lý độ phức tạp**: Giao diện đơn giản che giấu logic phức tạp bên dưới
