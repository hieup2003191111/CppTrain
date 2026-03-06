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
