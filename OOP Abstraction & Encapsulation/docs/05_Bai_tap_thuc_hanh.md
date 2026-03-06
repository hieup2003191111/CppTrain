# Bài tập thực hành về Abstraction và Encapsulation trong phần mềm ô tô

## Bài tập 1: Hệ thống quản lý động cơ đơn giản

**Mục tiêu**: Tạo một hệ thống quản lý động cơ đơn giản sử dụng các nguyên tắc Abstraction và Encapsulation.

**Yêu cầu**:
1. Tạo một lớp trừu tượng `Engine` với các phương thức thuần ảo: `start()`, `stop()`, `accelerate(double)`, và `getStatus()`
2. Triển khai hai lớp kế thừa cụ thể: `GasolineEngine` và `ElectricEngine`
3. Mỗi loại động cơ có các thuộc tính và hành vi riêng được đóng gói
4. Tạo lớp `VehicleEngineManager` sử dụng đối tượng `Engine` để điều khiển động cơ xe

**Tệp**: `engine_management.cpp`

```cpp
#include <iostream>
#include <string>

// Lớp trừu tượng cho động cơ (Abstraction)
class Engine {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void accelerate(double throttlePosition) = 0;
    virtual std::string getStatus() const = 0;
    virtual ~Engine() {}
};

// Lớp cụ thể: Động cơ xăng
class GasolineEngine : public Engine {
private:
    // Các thuộc tính được đóng gói (Encapsulation)
    bool isRunning;
    double rpm;
    double fuelLevel;
    double engineTemperature;
    
public:
    GasolineEngine(double initialFuelLevel = 100.0)
        : isRunning(false), rpm(0), fuelLevel(initialFuelLevel), engineTemperature(25.0) {}
    
    void start() override {
        if (fuelLevel > 0) {
            isRunning = true;
            rpm = 800; // Idle RPM
            engineTemperature += 10;
            std::cout << "Gasoline engine started. RPM: " << rpm << std::endl;
        } else {
            std::cout << "Cannot start: Out of fuel!" << std::endl;
        }
    }
    
    void stop() override {
        if (isRunning) {
            isRunning = false;
            rpm = 0;
            std::cout << "Gasoline engine stopped." << std::endl;
        }
    }
    
    void accelerate(double throttlePosition) override {
        if (!isRunning) {
            std::cout << "Engine is not running!" << std::endl;
            return;
        }
        
        if (throttlePosition < 0.0) throttlePosition = 0.0;
        if (throttlePosition > 1.0) throttlePosition = 1.0;
        
        // Tính toán RPM dựa trên vị trí bướm ga
        rpm = 800 + (throttlePosition * 6200); // Max 7000 RPM
        
        // Tiêu thụ nhiên liệu
        fuelLevel -= throttlePosition * 0.5;
        if (fuelLevel < 0) fuelLevel = 0;
        
        // Tăng nhiệt độ động cơ
        engineTemperature += throttlePosition * 5.0;
        
        std::cout << "Gasoline engine accelerating. RPM: " << rpm << std::endl;
    }
    
    std::string getStatus() const override {
        std::string status = "Gasoline Engine Status:\n";
        status += "Running: " + std::string(isRunning ? "Yes" : "No") + "\n";
        status += "RPM: " + std::to_string(rpm) + "\n";
        status += "Fuel Level: " + std::to_string(fuelLevel) + "%\n";
        status += "Temperature: " + std::to_string(engineTemperature) + "°C\n";
        return status;
    }
    
    // Các phương thức bổ sung đặc thù cho động cơ xăng
    void refuel(double amount) {
        fuelLevel += amount;
        if (fuelLevel > 100.0) fuelLevel = 100.0;
        std::cout << "Refueled. New fuel level: " << fuelLevel << "%" << std::endl;
    }
};

// Lớp cụ thể: Động cơ điện
class ElectricEngine : public Engine {
private:
    // Các thuộc tính được đóng gói (Encapsulation)
    bool isRunning;
    double power;  // kW
    double batteryLevel; // %
    double motorTemperature;
    
public:
    ElectricEngine(double initialBatteryLevel = 100.0)
        : isRunning(false), power(0), batteryLevel(initialBatteryLevel), motorTemperature(25.0) {}
    
    void start() override {
        if (batteryLevel > 0) {
            isRunning = true;
            power = 5.0; // Idle power consumption in kW
            std::cout << "Electric motor started. Power: " << power << " kW" << std::endl;
        } else {
            std::cout << "Cannot start: Battery depleted!" << std::endl;
        }
    }
    
    void stop() override {
        if (isRunning) {
            isRunning = false;
            power = 0;
            std::cout << "Electric motor stopped." << std::endl;
        }
    }
    
    void accelerate(double throttlePosition) override {
        if (!isRunning) {
            std::cout << "Motor is not running!" << std::endl;
            return;
        }
        
        if (throttlePosition < 0.0) throttlePosition = 0.0;
        if (throttlePosition > 1.0) throttlePosition = 1.0;
        
        // Tính toán công suất dựa trên vị trí bướm ga
        power = 5.0 + (throttlePosition * 245.0); // Max 250 kW
        
        // Tiêu thụ pin
        batteryLevel -= throttlePosition * 0.3;
        if (batteryLevel < 0) batteryLevel = 0;
        
        // Tăng nhiệt độ động cơ
        motorTemperature += throttlePosition * 3.0;
        
        std::cout << "Electric motor accelerating. Power: " << power << " kW" << std::endl;
    }
    
    std::string getStatus() const override {
        std::string status = "Electric Engine Status:\n";
        status += "Running: " + std::string(isRunning ? "Yes" : "No") + "\n";
        status += "Power: " + std::to_string(power) + " kW\n";
        status += "Battery Level: " + std::to_string(batteryLevel) + "%\n";
        status += "Motor Temperature: " + std::to_string(motorTemperature) + "°C\n";
        return status;
    }
    
    // Các phương thức bổ sung đặc thù cho động cơ điện
    void charge(double amount) {
        batteryLevel += amount;
        if (batteryLevel > 100.0) batteryLevel = 100.0;
        std::cout << "Charged. New battery level: " << batteryLevel << "%" << std::endl;
    }
    
    void enableRegenerativeBraking() {
        if (isRunning) {
            batteryLevel += 0.5;
            if (batteryLevel > 100.0) batteryLevel = 100.0;
            std::cout << "Regenerative braking enabled. Battery level: " << batteryLevel << "%" << std::endl;
        }
    }
};

// Lớp quản lý động cơ sử dụng abstraction
class VehicleEngineManager {
private:
    Engine* engine;  // Tham chiếu đến lớp trừu tượng

public:
    VehicleEngineManager(Engine* eng) : engine(eng) {}
    
    void startEngine() {
        engine->start();
    }
    
    void stopEngine() {
        engine->stop();
    }
    
    void accelerate(double throttlePosition) {
        engine->accelerate(throttlePosition);
    }
    
    void displayEngineStatus() {
        std::cout << engine->getStatus() << std::endl;
    }
};

// Hàm main để kiểm thử
int main() {
    std::cout << "==== Testing Gasoline Engine ====" << std::endl;
    GasolineEngine gasEngine(75.0);
    VehicleEngineManager gasCar(&gasEngine);
    
    gasCar.startEngine();
    gasCar.displayEngineStatus();
    
    gasCar.accelerate(0.5); // 50% throttle
    gasCar.displayEngineStatus();
    
    gasEngine.refuel(10.0);
    gasCar.stopEngine();
    gasCar.displayEngineStatus();
    
    std::cout << "\n==== Testing Electric Engine ====" << std::endl;
    ElectricEngine electricEngine(80.0);
    VehicleEngineManager electricCar(&electricEngine);
    
    electricCar.startEngine();
    electricCar.displayEngineStatus();
    
    electricCar.accelerate(0.7); // 70% throttle
    electricCar.displayEngineStatus();
    
    electricEngine.enableRegenerativeBraking();
    electricEngine.charge(15.0);
    
    electricCar.stopEngine();
    electricCar.displayEngineStatus();
    
    return 0;
}
```

## Bài tập 2: Hệ thống cảm biến ô tô

**Mục tiêu**: Thiết kế một hệ thống cảm biến ô tô sử dụng Abstraction và Encapsulation.

**Yêu cầu**:
1. Tạo lớp trừu tượng `Sensor` với phương thức thuần ảo `readData()` và `getType()`
2. Triển khai các cảm biến cụ thể: `TemperatureSensor`, `PressureSensor`, và `ProximitySensor`
3. Tạo lớp `SensorManager` để quản lý và thu thập dữ liệu từ tất cả cảm biến
4. Đảm bảo thông tin nội bộ của mỗi cảm biến được đóng gói và bảo vệ

**Tệp**: `sensor_system.cpp`

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

// Lớp cơ sở trừu tượng cho cảm biến (Abstraction)
class Sensor {
public:
    virtual double readData() = 0;
    virtual std::string getType() const = 0;
    virtual void calibrate() = 0;
    virtual std::string getStatus() const = 0;
    virtual ~Sensor() {}

protected:
    double lastReading;
    bool isCalibrated;
    time_t lastCalibrationTime;
    std::string sensorID;
};

// Cảm biến nhiệt độ
class TemperatureSensor : public Sensor {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    double minTemp;
    double maxTemp;
    double calibrationOffset;
    
    // Phương thức private
    double simulateTemperatureReading() const {
        // Mô phỏng đọc nhiệt độ từ phần cứng
        // Trong thực tế, đây sẽ là giao tiếp với phần cứng thực
        return minTemp + (rand() % static_cast<int>((maxTemp - minTemp) * 10)) / 10.0;
    }

public:
    TemperatureSensor(const std::string& id, double min = -40.0, double max = 125.0)
        : minTemp(min), maxTemp(max), calibrationOffset(0.0) {
        sensorID = id;
        isCalibrated = false;
        lastReading = 20.0; // Giá trị khởi tạo
        lastCalibrationTime = 0;
    }
    
    double readData() override {
        double rawValue = simulateTemperatureReading();
        
        // Áp dụng hiệu chuẩn
        lastReading = rawValue + calibrationOffset;
        
        return lastReading;
    }
    
    std::string getType() const override {
        return "Temperature Sensor";
    }
    
    void calibrate() override {
        // Quy trình hiệu chuẩn
        double knownTemp = 25.0; // Nhiệt độ chuẩn
        double measuredTemp = simulateTemperatureReading();
        
        calibrationOffset = knownTemp - measuredTemp;
        isCalibrated = true;
        lastCalibrationTime = time(nullptr);
        
        std::cout << "Temperature sensor " << sensorID << " calibrated with offset: " 
                  << calibrationOffset << "°C" << std::endl;
    }
    
    std::string getStatus() const override {
        std::string status = "Temperature Sensor " + sensorID + ":\n";
        status += "Range: " + std::to_string(minTemp) + "°C to " + std::to_string(maxTemp) + "°C\n";
        status += "Last reading: " + std::to_string(lastReading) + "°C\n";
        status += "Calibrated: " + std::string(isCalibrated ? "Yes" : "No") + "\n";
        
        if (isCalibrated) {
            char buffer[80];
            struct tm* timeinfo = localtime(&lastCalibrationTime);
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
            status += "Last calibration: " + std::string(buffer) + "\n";
        }
        
        return status;
    }
    
    // Các phương thức bổ sung đặc thù
    double getMinTemperature() const {
        return minTemp;
    }
    
    double getMaxTemperature() const {
        return maxTemp;
    }
};

// Cảm biến áp suất
class PressureSensor : public Sensor {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    double minPressure; // kPa
    double maxPressure; // kPa
    double calibrationFactor;
    std::string location; // Vị trí lắp đặt trên xe
    
    // Phương thức private
    double simulatePressureReading() const {
        // Mô phỏng đọc áp suất
        return minPressure + (rand() % static_cast<int>((maxPressure - minPressure) * 10)) / 10.0;
    }

public:
    PressureSensor(const std::string& id, const std::string& location, 
                  double min = 0.0, double max = 500.0)
        : minPressure(min), maxPressure(max), calibrationFactor(1.0), location(location) {
        sensorID = id;
        isCalibrated = false;
        lastReading = 101.3; // áp suất khí quyển tiêu chuẩn (kPa)
        lastCalibrationTime = 0;
    }
    
    double readData() override {
        double rawValue = simulatePressureReading();
        
        // Áp dụng hệ số hiệu chuẩn
        lastReading = rawValue * calibrationFactor;
        
        return lastReading;
    }
    
    std::string getType() const override {
        return "Pressure Sensor";
    }
    
    void calibrate() override {
        // Quy trình hiệu chuẩn
        double knownPressure = 101.3; // áp suất chuẩn (kPa)
        double measuredPressure = simulatePressureReading();
        
        if (measuredPressure > 0) {
            calibrationFactor = knownPressure / measuredPressure;
        } else {
            calibrationFactor = 1.0; // Tránh chia cho 0
        }
        
        isCalibrated = true;
        lastCalibrationTime = time(nullptr);
        
        std::cout << "Pressure sensor " << sensorID << " calibrated with factor: " 
                  << calibrationFactor << std::endl;
    }
    
    std::string getStatus() const override {
        std::string status = "Pressure Sensor " + sensorID + " (" + location + "):\n";
        status += "Range: " + std::to_string(minPressure) + " to " + std::to_string(maxPressure) + " kPa\n";
        status += "Last reading: " + std::to_string(lastReading) + " kPa\n";
        status += "Calibrated: " + std::string(isCalibrated ? "Yes" : "No") + "\n";
        
        if (isCalibrated) {
            char buffer[80];
            struct tm* timeinfo = localtime(&lastCalibrationTime);
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
            status += "Last calibration: " + std::string(buffer) + "\n";
        }
        
        return status;
    }
    
    // Các phương thức bổ sung đặc thù
    std::string getLocation() const {
        return location;
    }
    
    void setWarningThreshold(double threshold) {
        if (threshold >= minPressure && threshold <= maxPressure) {
            std::cout << "Warning threshold for " << sensorID << " set to " 
                      << threshold << " kPa" << std::endl;
        }
    }
};

// Cảm biến khoảng cách
class ProximitySensor : public Sensor {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    double maxRange; // mét
    std::string location; // Vị trí trên xe (front, rear, etc.)
    bool isActive;
    double noiseThreshold;
    
    // Phương thức private
    double simulateDistanceReading() const {
        // Mô phỏng đọc khoảng cách
        // Phân phối có xu hướng về xa (giảm khả năng phát hiện vật thể gần)
        double randomFactor = (rand() % 100) / 100.0;
        return maxRange * randomFactor * randomFactor;
    }

public:
    ProximitySensor(const std::string& id, const std::string& location, double range = 3.0)
        : maxRange(range), location(location), isActive(true), noiseThreshold(0.1) {
        sensorID = id;
        isCalibrated = false;
        lastReading = maxRange; // Không có vật thể nào
        lastCalibrationTime = 0;
    }
    
    double readData() override {
        if (!isActive) {
            return -1.0; // Cảm biến không hoạt động
        }
        
        double rawDistance = simulateDistanceReading();
        
        // Lọc nhiễu
        if (rawDistance < noiseThreshold) {
            rawDistance = noiseThreshold;
        }
        
        lastReading = rawDistance;
        return lastReading;
    }
    
    std::string getType() const override {
        return "Proximity Sensor";
    }
    
    void calibrate() override {
        // Quy trình hiệu chuẩn - đặt cảm biến ở khoảng cách đã biết
        isCalibrated = true;
        lastCalibrationTime = time(nullptr);
        noiseThreshold = 0.05; // Giảm ngưỡng nhiễu sau khi hiệu chuẩn
        
        std::cout << "Proximity sensor " << sensorID << " calibrated. Noise threshold: " 
                  << noiseThreshold << " m" << std::endl;
    }
    
    std::string getStatus() const override {
        std::string status = "Proximity Sensor " + sensorID + " (" + location + "):\n";
        status += "Range: 0 to " + std::to_string(maxRange) + " m\n";
        
        if (isActive) {
            status += "Last reading: " + std::to_string(lastReading) + " m\n";
        } else {
            status += "Status: Inactive\n";
        }
        
        status += "Calibrated: " + std::string(isCalibrated ? "Yes" : "No") + "\n";
        
        if (isCalibrated) {
            char buffer[80];
            struct tm* timeinfo = localtime(&lastCalibrationTime);
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
            status += "Last calibration: " + std::string(buffer) + "\n";
        }
        
        return status;
    }
    
    // Các phương thức bổ sung đặc thù
    void activate() {
        isActive = true;
        std::cout << "Proximity sensor " << sensorID << " activated" << std::endl;
    }
    
    void deactivate() {
        isActive = false;
        std::cout << "Proximity sensor " << sensorID << " deactivated" << std::endl;
    }
    
    bool isObstacleDetected(double threshold = 0.5) const {
        return isActive && lastReading <= threshold;
    }
};

// Quản lý hệ thống cảm biến
class SensorManager {
private:
    std::vector<Sensor*> sensors;

public:
    // Thêm cảm biến vào hệ thống
    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
    }
    
    // Đọc dữ liệu từ tất cả cảm biến
    void readAllSensors() {
        for (auto sensor : sensors) {
            double reading = sensor->readData();
            std::cout << sensor->getType() << " (" << sensor->getStatus().substr(0, sensor->getStatus().find('\n')) << "): " 
                      << reading;
            
            // Thêm đơn vị đo lường phù hợp
            if (sensor->getType() == "Temperature Sensor") {
                std::cout << "°C";
            } else if (sensor->getType() == "Pressure Sensor") {
                std::cout << " kPa";
            } else if (sensor->getType() == "Proximity Sensor") {
                std::cout << " m";
            }
            
            std::cout << std::endl;
        }
    }
    
    // Hiệu chuẩn tất cả cảm biến
    void calibrateAllSensors() {
        std::cout << "Calibrating all sensors..." << std::endl;
        for (auto sensor : sensors) {
            sensor->calibrate();
        }
    }
    
    // Hiển thị trạng thái tất cả cảm biến
    void displayAllSensorStatus() {
        std::cout << "\n===== SENSOR SYSTEM STATUS =====" << std::endl;
        for (auto sensor : sensors) {
            std::cout << sensor->getStatus() << std::endl;
        }
    }
    
    // Giải phóng bộ nhớ khi hủy đối tượng
    ~SensorManager() {
        for (auto sensor : sensors) {
            delete sensor;
        }
    }
};

// Hàm main để kiểm thử
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Tạo quản lý cảm biến
    SensorManager sensorSystem;
    
    // Tạo và thêm các cảm biến
    sensorSystem.addSensor(new TemperatureSensor("TEMP001", -30, 120));
    sensorSystem.addSensor(new PressureSensor("PRES001", "Engine Oil", 0, 600));
    sensorSystem.addSensor(new PressureSensor("PRES002", "Tire Front-Left", 150, 350));
    sensorSystem.addSensor(new ProximitySensor("PROX001", "Front", 2.0));
    sensorSystem.addSensor(new ProximitySensor("PROX002", "Rear", 1.5));
    
    // Đọc dữ liệu từ tất cả cảm biến
    std::cout << "Initial readings:" << std::endl;
    sensorSystem.readAllSensors();
    
    // Hiệu chuẩn tất cả cảm biến
    sensorSystem.calibrateAllSensors();
    
    // Đọc lại dữ liệu sau khi hiệu chuẩn
    std::cout << "\nReadings after calibration:" << std::endl;
    sensorSystem.readAllSensors();
    
    // Hiển thị trạng thái chi tiết
    sensorSystem.displayAllSensorStatus();
    
    return 0;
}
```

## Bài tập 3: Hệ thống đa phương tiện (Media System)

**Mục tiêu**: Xây dựng một hệ thống đa phương tiện đơn giản cho ô tô sử dụng Abstraction và Encapsulation.

**Yêu cầu**:
1. Tạo lớp trừu tượng `MediaPlayer` với các phương thức thuần ảo cơ bản
2. Triển khai các lớp con `AudioPlayer` và `VideoPlayer`
3. Tạo lớp `MediaSystem` để quản lý các đối tượng người dùng và hiển thị
4. Sử dụng Encapsulation để bảo vệ các thuộc tính và phương thức nội bộ

**Tệp**: `media_system.cpp`

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Định nghĩa các enum và cấu trúc cần thiết
enum class MediaType {
    Audio,
    Video,
    Image,
    Unknown
};

enum class PlaybackStatus {
    Playing,
    Paused,
    Stopped,
    Error
};

struct MediaInfo {
    std::string title;
    std::string artist;
    std::string album;
    int year;
    int duration; // thời lượng theo giây
    MediaType type;
    
    MediaInfo() : year(0), duration(0), type(MediaType::Unknown) {}
};

// Lớp trừu tượng cho Media Player (Abstraction)
class MediaPlayer {
public:
    // Phương thức thuần ảo
    virtual bool loadMedia(const std::string& path) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void seekTo(int position) = 0;
    virtual PlaybackStatus getStatus() const = 0;
    virtual MediaInfo getMediaInfo() const = 0;
    
    // Destructor ảo
    virtual ~MediaPlayer() {}
    
protected:
    // Thuộc tính chung
    PlaybackStatus status;
    MediaInfo mediaInfo;
    std::string currentFilePath;
    int currentPosition; // vị trí hiện tại (giây)
    
    // Phương thức trợ giúp
    std::string getFileExtension(const std::string& path) const {
        size_t dotPos = path.find_last_of(".");
        if (dotPos != std::string::npos) {
            return path.substr(dotPos + 1);
        }
        return "";
    }
    
    std::string getFileName(const std::string& path) const {
        size_t slashPos = path.find_last_of("/\\");
        if (slashPos != std::string::npos) {
            return path.substr(slashPos + 1);
        }
        return path;
    }
};

// Lớp cụ thể: Audio Player
class AudioPlayer : public MediaPlayer {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    int volume; // 0-100
    bool isMuted;
    std::vector<std::string> supportedFormats;
    
    // Phương thức private
    void extractMetadata(const std::string& path) {
        // Mô phỏng trích xuất metadata từ tệp âm thanh
        mediaInfo.title = getFileName(path);
        mediaInfo.title = mediaInfo.title.substr(0, mediaInfo.title.find_last_of("."));
        
        // Giả lập trích xuất metadata
        if (path.find("song") != std::string::npos) {
            mediaInfo.artist = "Example Artist";
            mediaInfo.album = "Example Album";
            mediaInfo.year = 2023;
            mediaInfo.duration = 180 + rand() % 180; // 3-6 phút
        } else {
            mediaInfo.artist = "Unknown Artist";
            mediaInfo.duration = 60 + rand() % 240; // 1-5 phút
        }
    }
    
    bool isFormatSupported(const std::string& extension) const {
        return std::find(supportedFormats.begin(), supportedFormats.end(), extension) != supportedFormats.end();
    }

public:
    AudioPlayer() : volume(50), isMuted(false) {
        status = PlaybackStatus::Stopped;
        currentPosition = 0;
        
        // Định dạng được hỗ trợ
        supportedFormats = {"mp3", "wav", "aac", "flac", "ogg"};
        
        mediaInfo.type = MediaType::Audio;
    }
    
    bool loadMedia(const std::string& path) override {
        std::string extension = getFileExtension(path);
        
        // Kiểm tra định dạng được hỗ trợ
        if (!isFormatSupported(extension)) {
            std::cout << "Unsupported audio format: " << extension << std::endl;
            return false;
        }
        
        currentFilePath = path;
        currentPosition = 0;
        status = PlaybackStatus::Stopped;
        
        // Trích xuất thông tin tệp
        extractMetadata(path);
        
        std::cout << "Loaded audio: " << mediaInfo.title << std::endl;
        return true;
    }
    
    void play() override {
        if (currentFilePath.empty()) {
            std::cout << "No audio file loaded" << std::endl;
            return;
        }
        
        if (status == PlaybackStatus::Paused) {
            std::cout << "Resuming audio: " << mediaInfo.title << std::endl;
        } else {
            std::cout << "Playing audio: " << mediaInfo.title << std::endl;
        }
        
        status = PlaybackStatus::Playing;
    }
    
    void pause() override {
        if (status == PlaybackStatus::Playing) {
            std::cout << "Audio paused" << std::endl;
            status = PlaybackStatus::Paused;
        }
    }
    
    void stop() override {
        if (status != PlaybackStatus::Stopped) {
            std::cout << "Audio stopped" << std::endl;
            status = PlaybackStatus::Stopped;
            currentPosition = 0;
        }
    }
    
    void seekTo(int position) override {
        if (position >= 0 && position < mediaInfo.duration) {
            currentPosition = position;
            std::cout << "Seek to " << formatTime(position) << std::endl;
        } else {
            std::cout << "Invalid position" << std::endl;
        }
    }
    
    PlaybackStatus getStatus() const override {
        return status;
    }
    
    MediaInfo getMediaInfo() const override {
        return mediaInfo;
    }
    
    // Các phương thức đặc thù của AudioPlayer
    void setVolume(int newVolume) {
        if (newVolume >= 0 && newVolume <= 100) {
            volume = newVolume;
            if (newVolume > 0) {
                isMuted = false;
            }
            std::cout << "Volume set to " << volume << "%" << std::endl;
        }
    }
    
    int getVolume() const {
        return isMuted ? 0 : volume;
    }
    
    void mute() {
        isMuted = true;
        std::cout << "Audio muted" << std::endl;
    }
    
    void unmute() {
        isMuted = false;
        std::cout << "Audio unmuted, volume: " << volume << "%" << std::endl;
    }
    
    bool isMutedState() const {
        return isMuted;
    }
    
    std::string formatTime(int seconds) const {
        int minutes = seconds / 60;
        int secs = seconds % 60;
        return std::to_string(minutes) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
    }
    
    std::string getPlaybackInfo() const {
        return formatTime(currentPosition) + " / " + formatTime(mediaInfo.duration);
    }
};

// Lớp cụ thể: Video Player
class VideoPlayer : public MediaPlayer {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    int volume; // 0-100
    bool isMuted;
    int brightness; // 0-100
    int contrast; // 0-100
    std::vector<std::string> supportedFormats;
    bool isFullscreen;
    
    // Phương thức private
    void extractMetadata(const std::string& path) {
        // Mô phỏng trích xuất metadata từ tệp video
        mediaInfo.title = getFileName(path);
        mediaInfo.title = mediaInfo.title.substr(0, mediaInfo.title.find_last_of("."));
        
        // Giả lập trích xuất metadata
        if (path.find("movie") != std::string::npos) {
            mediaInfo.artist = "Example Director";
            mediaInfo.year = 2020;
            mediaInfo.duration = 5400 + rand() % 3600; // 90-150 phút
        } else {
            mediaInfo.artist = "Unknown";
            mediaInfo.duration = 120 + rand() % 480; // 2-10 phút
        }
    }
    
    bool isFormatSupported(const std::string& extension) const {
        return std::find(supportedFormats.begin(), supportedFormats.end(), extension) != supportedFormats.end();
    }

public:
    VideoPlayer() : volume(50), isMuted(false), brightness(50), contrast(50), isFullscreen(false) {
        status = PlaybackStatus::Stopped;
        currentPosition = 0;
        
        // Định dạng được hỗ trợ
        supportedFormats = {"mp4", "avi", "mkv", "mov", "wmv"};
        
        mediaInfo.type = MediaType::Video;
    }
    
    bool loadMedia(const std::string& path) override {
        std::string extension = getFileExtension(path);
        
        // Kiểm tra định dạng được hỗ trợ
        if (!isFormatSupported(extension)) {
            std::cout << "Unsupported video format: " << extension << std::endl;
            return false;
        }
        
        currentFilePath = path;
        currentPosition = 0;
        status = PlaybackStatus::Stopped;
        
        // Trích xuất thông tin tệp
        extractMetadata(path);
        
        std::cout << "Loaded video: " << mediaInfo.title << std::endl;
        return true;
    }
    
    void play() override {
        if (currentFilePath.empty()) {
            std::cout << "No video file loaded" << std::endl;
            return;
        }
        
        if (status == PlaybackStatus::Paused) {
            std::cout << "Resuming video: " << mediaInfo.title << std::endl;
        } else {
            std::cout << "Playing video: " << mediaInfo.title << std::endl;
        }
        
        status = PlaybackStatus::Playing;
    }
    
    void pause() override {
        if (status == PlaybackStatus::Playing) {
            std::cout << "Video paused" << std::endl;
            status = PlaybackStatus::Paused;
        }
    }
    
    void stop() override {
        if (status != PlaybackStatus::Stopped) {
            std::cout << "Video stopped" << std::endl;
            status = PlaybackStatus::Stopped;
            currentPosition = 0;
        }
    }
    
    void seekTo(int position) override {
        if (position >= 0 && position < mediaInfo.duration) {
            currentPosition = position;
            std::cout << "Seek to " << formatTime(position) << std::endl;
        } else {
            std::cout << "Invalid position" << std::endl;
        }
    }
    
    PlaybackStatus getStatus() const override {
        return status;
    }
    
    MediaInfo getMediaInfo() const override {
        return mediaInfo;
    }
    
    // Các phương thức đặc thù của VideoPlayer
    void setVolume(int newVolume) {
        if (newVolume >= 0 && newVolume <= 100) {
            volume = newVolume;
            if (newVolume > 0) {
                isMuted = false;
            }
            std::cout << "Volume set to " << volume << "%" << std::endl;
        }
    }
    
    void setBrightness(int value) {
        if (value >= 0 && value <= 100) {
            brightness = value;
            std::cout << "Brightness set to " << brightness << "%" << std::endl;
        }
    }
    
    void setContrast(int value) {
        if (value >= 0 && value <= 100) {
            contrast = value;
            std::cout << "Contrast set to " << contrast << "%" << std::endl;
        }
    }
    
    void toggleFullscreen() {
        isFullscreen = !isFullscreen;
        std::cout << "Fullscreen mode: " << (isFullscreen ? "On" : "Off") << std::endl;
    }
    
    bool getFullscreenMode() const {
        return isFullscreen;
    }
    
    std::string formatTime(int seconds) const {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        int secs = seconds % 60;
        
        if (hours > 0) {
            return std::to_string(hours) + ":" + 
                  (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + 
                  (secs < 10 ? "0" : "") + std::to_string(secs);
        } else {
            return std::to_string(minutes) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
        }
    }
    
    std::string getPlaybackInfo() const {
        return formatTime(currentPosition) + " / " + formatTime(mediaInfo.duration);
    }
    
    std::string getVideoSettings() const {
        return "Brightness: " + std::to_string(brightness) + "%, Contrast: " + std::to_string(contrast) + "%";
    }
};

// Lớp quản lý hệ thống media
class MediaSystem {
private:
    AudioPlayer audioPlayer;
    VideoPlayer videoPlayer;
    MediaPlayer* activePlayer; // Trỏ tới người chơi đang hoạt động
    
    // Playlist
    std::vector<std::string> playlist;
    int currentPlaylistIndex;
    
    // Thông tin hiển thị
    bool displayEnabled;
    bool isVehicleMoving;

public:
    MediaSystem() : activePlayer(nullptr), currentPlaylistIndex(-1), 
                   displayEnabled(true), isVehicleMoving(false) {}
    
    void loadAudioFile(const std::string& path) {
        if (audioPlayer.loadMedia(path)) {
            activePlayer = &audioPlayer;
        }
    }
    
    void loadVideoFile(const std::string& path) {
        if (isVehicleMoving) {
            std::cout << "Cannot play video while vehicle is moving" << std::endl;
            return;
        }
        
        if (videoPlayer.loadMedia(path)) {
            activePlayer = &videoPlayer;
        }
    }
    
    void addToPlaylist(const std::string& path) {
        playlist.push_back(path);
        std::cout << "Added to playlist: " << path << std::endl;
        
        // Nếu đây là mục đầu tiên, tải nó
        if (playlist.size() == 1) {
            currentPlaylistIndex = 0;
            loadMediaFromPlaylist(currentPlaylistIndex);
        }
    }
    
    void clearPlaylist() {
        playlist.clear();
        currentPlaylistIndex = -1;
        std::cout << "Playlist cleared" << std::endl;
    }
    
    void nextTrack() {
        if (playlist.empty()) {
            std::cout << "Playlist is empty" << std::endl;
            return;
        }
        
        currentPlaylistIndex = (currentPlaylistIndex + 1) % playlist.size();
        loadMediaFromPlaylist(currentPlaylistIndex);
        play();
    }
    
    void previousTrack() {
        if (playlist.empty()) {
            std::cout << "Playlist is empty" << std::endl;
            return;
        }
        
        currentPlaylistIndex = (currentPlaylistIndex - 1 + playlist.size()) % playlist.size();
        loadMediaFromPlaylist(currentPlaylistIndex);
        play();
    }
    
    void play() {
        if (activePlayer) {
            activePlayer->play();
        } else {
            std::cout << "No media selected" << std::endl;
        }
    }
    
    void pause() {
        if (activePlayer) {
            activePlayer->pause();
        } else {
            std::cout << "No media selected" << std::endl;
        }
    }
    
    void stop() {
        if (activePlayer) {
            activePlayer->stop();
        } else {
            std::cout << "No media selected" << std::endl;
        }
    }
    
    void setVolume(int volume) {
        audioPlayer.setVolume(volume);
        videoPlayer.setVolume(volume);
    }
    
    void setDisplayEnabled(bool enabled) {
        displayEnabled = enabled;
        std::cout << "Display " << (enabled ? "enabled" : "disabled") << std::endl;
    }
    
    void setVehicleMovingStatus(bool moving) {
        isVehicleMoving = moving;
        std::cout << "Vehicle moving status: " << (moving ? "Moving" : "Stopped") << std::endl;
        
        // Nếu xe đang di chuyển và đang phát video, tạm dừng video
        if (moving && activePlayer == &videoPlayer && 
            videoPlayer.getStatus() == PlaybackStatus::Playing) {
            std::cout << "Video playback paused for safety" << std::endl;
            videoPlayer.pause();
        }
    }
    
    void displayCurrentMedia() {
        if (!activePlayer) {
            std::cout << "No media playing" << std::endl;
            return;
        }
        
        MediaInfo info = activePlayer->getMediaInfo();
        
        std::cout << "\n===== Current Media =====" << std::endl;
        std::cout << "Title: " << info.title << std::endl;
        
        if (!info.artist.empty()) {
            std::cout << "Artist: " << info.artist << std::endl;
        }
        
        if (!info.album.empty() && info.type == MediaType::Audio) {
            std::cout << "Album: " << info.album << std::endl;
        }
        
        if (info.year > 0) {
            std::cout << "Year: " << info.year << std::endl;
        }
        
        std::cout << "Type: " << (info.type == MediaType::Audio ? "Audio" : "Video") << std::endl;
        
        PlaybackStatus status = activePlayer->getStatus();
        std::cout << "Status: ";
        switch (status) {
            case PlaybackStatus::Playing:
                std::cout << "Playing";
                break;
            case PlaybackStatus::Paused:
                std::cout << "Paused";
                break;
            case PlaybackStatus::Stopped:
                std::cout << "Stopped";
                break;
            case PlaybackStatus::Error:
                std::cout << "Error";
                break;
        }
        std::cout << std::endl;
        
        // Display playback information
        if (activePlayer == &audioPlayer) {
            std::cout << "Playback: " << audioPlayer.getPlaybackInfo() << std::endl;
            std::cout << "Volume: " << audioPlayer.getVolume() << "%" << 
                     (audioPlayer.isMutedState() ? " (Muted)" : "") << std::endl;
        } 
        else if (activePlayer == &videoPlayer) {
            std::cout << "Playback: " << videoPlayer.getPlaybackInfo() << std::endl;
            std::cout << videoPlayer.getVideoSettings() << std::endl;
            std::cout << "Fullscreen: " << (videoPlayer.getFullscreenMode() ? "Yes" : "No") << std::endl;
        }
        
        // Display playlist information
        if (!playlist.empty()) {
            std::cout << "\nPlaylist (" << currentPlaylistIndex + 1 << "/" << playlist.size() << ")" << std::endl;
            for (size_t i = 0; i < playlist.size(); ++i) {
                if (i == currentPlaylistIndex) {
                    std::cout << "> ";
                } else {
                    std::cout << "  ";
                }
                std::cout << i + 1 << ". " << playlist[i] << std::endl;
            }
        }
    }

private:
    void loadMediaFromPlaylist(int index) {
        if (index >= 0 && index < static_cast<int>(playlist.size())) {
            std::string path = playlist[index];
            std::string extension = path.substr(path.find_last_of(".") + 1);
            
            // Tự động xác định loại media
            if (extension == "mp3" || extension == "wav" || extension == "aac" || 
                extension == "flac" || extension == "ogg") {
                loadAudioFile(path);
            } 
            else if (extension == "mp4" || extension == "avi" || extension == "mkv" || 
                     extension == "mov" || extension == "wmv") {
                loadVideoFile(path);
            }
            else {
                std::cout << "Unsupported file format: " << extension << std::endl;
            }
        }
    }
};

// Hàm main để kiểm thử
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(static_cast<unsigned int>(time(nullptr)));
    
    MediaSystem carMediaSystem;
    
    // Thêm các tệp vào danh sách phát
    carMediaSystem.addToPlaylist("music/song1.mp3");
    carMediaSystem.addToPlaylist("music/song2.mp3");
    carMediaSystem.addToPlaylist("videos/movie1.mp4");
    
    // Phát media
    carMediaSystem.play();
    carMediaSystem.displayCurrentMedia();
    
    // Thiết lập âm lượng
    carMediaSystem.setVolume(70);
    
    // Chuyển đến bài tiếp theo
    carMediaSystem.nextTrack();
    carMediaSystem.displayCurrentMedia();
    
    // Mô phỏng xe đang di chuyển - sẽ ảnh hưởng đến khả năng phát video
    carMediaSystem.setVehicleMovingStatus(true);
    
    // Thử chuyển đến video
    carMediaSystem.nextTrack();
    carMediaSystem.displayCurrentMedia();
    
    // Xe dừng lại - có thể phát video
    carMediaSystem.setVehicleMovingStatus(false);
    carMediaSystem.play();
    carMediaSystem.displayCurrentMedia();
    
    return 0;
}
```

Hãy sử dụng các ví dụ này để hiểu và thực hành các khái niệm Abstraction và Encapsulation trong ngữ cảnh phát triển phần mềm ô tô. Mỗi bài tập tập trung vào một hệ thống khác nhau trong ô tô hiện đại, giúp minh họa cách áp dụng OOP vào các vấn đề thực tế.
