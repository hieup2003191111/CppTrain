// Bài tập thực hành: Hệ thống chẩn đoán trên xe (On-board Diagnostics)
// Học viên hoàn thiện các lớp còn thiếu và phương thức được đánh dấu TODO

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>

// Enum mã lỗi
enum class DiagnosticCode {
    P0100, // Mass Air Flow Sensor
    P0200, // Fuel Injector Circuit
    P0300, // Random Misfire
    P0400, // EGR System
    P0500  // Vehicle Speed Sensor
};

// Cấu trúc thông tin lỗi
struct DiagnosticInfo {
    DiagnosticCode code;
    std::string description;
    std::string subsystem;
    int severity; // 1-10, 10 là nghiêm trọng nhất
    time_t timestamp;
    
    DiagnosticInfo(DiagnosticCode c, const std::string& desc, const std::string& sys, int sev)
        : code(c), description(desc), subsystem(sys), severity(sev), timestamp(time(nullptr)) {}
};

// Lớp trừu tượng cho hệ thống có thể chẩn đoán
class DiagnosticCapable {
public:
    virtual void runDiagnostics() = 0;
    virtual std::vector<DiagnosticInfo> getDiagnosticResults() const = 0;
    virtual bool hasActiveErrors() const = 0;
    virtual void clearErrors() = 0;
    virtual ~DiagnosticCapable() {}
};

// Lớp Engine - Hệ thống động cơ
class Engine : public DiagnosticCapable {
private:
    bool running;
    double rpm;
    double temperature;
    double fuelLevel;
    std::vector<DiagnosticInfo> diagnosticResults;
    
    // Phương thức mô phỏng lỗi
    void simulateErrors() {
        // Xóa các lỗi cũ
        diagnosticResults.clear();
        
        // Giả lập lỗi ngẫu nhiên
        if (temperature > 95.0) {
            // Lỗi quá nhiệt
            diagnosticResults.push_back(DiagnosticInfo(
                DiagnosticCode::P0100,
                "Engine Overheating",
                "Cooling System",
                8
            ));
        }
        
        if (fuelLevel < 10.0 && running) {
            // Cảnh báo nhiên liệu thấp
            diagnosticResults.push_back(DiagnosticInfo(
                DiagnosticCode::P0200,
                "Low Fuel Warning",
                "Fuel System",
                3
            ));
        }
        
        // 5% cơ hội có lỗi ngẫu nhiên khác
        if (rand() % 100 < 5) {
            diagnosticResults.push_back(DiagnosticInfo(
                DiagnosticCode::P0300,
                "Random/Multiple Cylinder Misfire Detected",
                "Ignition System",
                7
            ));
        }
    }
    
public:
    Engine() : running(false), rpm(0.0), temperature(25.0), fuelLevel(100.0) {}
    
    void start() {
        if (!running && fuelLevel > 0) {
            running = true;
            rpm = 800.0; // Idle RPM
            std::cout << "Engine started" << std::endl;
        } else if (running) {
            std::cout << "Engine already running" << std::endl;
        } else {
            std::cout << "Cannot start: No fuel" << std::endl;
        }
    }
    
    void stop() {
        if (running) {
            running = false;
            rpm = 0.0;
            std::cout << "Engine stopped" << std::endl;
        } else {
            std::cout << "Engine already stopped" << std::endl;
        }
    }
    
    void setRPM(double newRPM) {
        if (running && newRPM >= 0) {
            rpm = newRPM;
            
            // Tăng nhiệt độ khi RPM cao
            if (rpm > 3000) {
                temperature += 0.1;
            }
        }
    }
    
    void consumeFuel(double amount) {
        fuelLevel -= amount;
        if (fuelLevel < 0) {
            fuelLevel = 0;
            if (running) {
                std::cout << "Engine stalled: Out of fuel" << std::endl;
                stop();
            }
        }
    }
    
    // Triển khai các phương thức của DiagnosticCapable
    void runDiagnostics() override {
        std::cout << "Running engine diagnostics..." << std::endl;
        simulateErrors();
    }
    
    std::vector<DiagnosticInfo> getDiagnosticResults() const override {
        return diagnosticResults;
    }
    
    bool hasActiveErrors() const override {
        return !diagnosticResults.empty();
    }
    
    void clearErrors() override {
        diagnosticResults.clear();
        std::cout << "Engine error codes cleared" << std::endl;
    }
    
    // Getters
    bool isRunning() const { return running; }
    double getRPM() const { return rpm; }
    double getTemperature() const { return temperature; }
    double getFuelLevel() const { return fuelLevel; }
    
    // Setter cho nhiên liệu
    void refuel(double amount) {
        if (amount > 0) {
            fuelLevel += amount;
            if (fuelLevel > 100) {
                fuelLevel = 100;
            }
            std::cout << "Refueled. New level: " << fuelLevel << "%" << std::endl;
        }
    }
};

// TODO: Học viên triển khai lớp TransmissionSystem kế thừa từ DiagnosticCapable
// Lớp này quản lý hộp số của xe


// TODO: Học viên triển khai lớp BrakeSystem kế thừa từ DiagnosticCapable
// Lớp này quản lý hệ thống phanh xe


// Lớp quản lý chẩn đoán tập trung
class DiagnosticSystem {
private:
    std::vector<DiagnosticCapable*> systems;
    std::map<DiagnosticCode, std::string> codeDescriptions;
    
    void initializeCodeDescriptions() {
        codeDescriptions[DiagnosticCode::P0100] = "Mass or Volume Air Flow Circuit";
        codeDescriptions[DiagnosticCode::P0200] = "Fuel Injection System";
        codeDescriptions[DiagnosticCode::P0300] = "Random/Multiple Cylinder Misfire Detected";
        codeDescriptions[DiagnosticCode::P0400] = "Exhaust Gas Recirculation Flow";
        codeDescriptions[DiagnosticCode::P0500] = "Vehicle Speed Sensor Circuit";
    }
    
public:
    DiagnosticSystem() {
        initializeCodeDescriptions();
    }
    
    void addSystem(DiagnosticCapable* system) {
        systems.push_back(system);
    }
    
    void runFullDiagnostics() {
        std::cout << "Running full vehicle diagnostics..." << std::endl;
        
        for (auto system : systems) {
            system->runDiagnostics();
        }
        
        std::cout << "Diagnostics complete." << std::endl;
    }
    
    void displayAllDiagnostics() {
        std::cout << "\n===== VEHICLE DIAGNOSTIC RESULTS =====" << std::endl;
        
        bool hasErrors = false;
        
        for (auto system : systems) {
            auto results = system->getDiagnosticResults();
            
            if (!results.empty()) {
                hasErrors = true;
                for (const auto& result : results) {
                    std::cout << "Code: " << codeToString(result.code) << std::endl;
                    std::cout << "Description: " << result.description << std::endl;
                    std::cout << "Subsystem: " << result.subsystem << std::endl;
                    std::cout << "Severity: " << result.severity << "/10" << std::endl;
                    
                    // Format timestamp
                    char buffer[80];
                    struct tm* timeinfo = localtime(&result.timestamp);
                    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
                    std::cout << "Time: " << buffer << std::endl;
                    
                    std::cout << "-------------------" << std::endl;
                }
            }
        }
        
        if (!hasErrors) {
            std::cout << "No errors detected. All systems operating normally." << std::endl;
        }
    }
    
    void clearAllErrors() {
        for (auto system : systems) {
            system->clearErrors();
        }
        std::cout << "All diagnostic codes cleared" << std::endl;
    }
    
    bool isVehicleHealthy() const {
        for (auto system : systems) {
            if (system->hasActiveErrors()) {
                return false;
            }
        }
        return true;
    }
    
    // Chuyển đổi mã sang chuỗi
    std::string codeToString(DiagnosticCode code) const {
        switch (code) {
            case DiagnosticCode::P0100: return "P0100";
            case DiagnosticCode::P0200: return "P0200";
            case DiagnosticCode::P0300: return "P0300";
            case DiagnosticCode::P0400: return "P0400";
            case DiagnosticCode::P0500: return "P0500";
            default: return "Unknown";
        }
    }
};

// Hàm main - mô phỏng hoạt động của hệ thống
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // TODO: Học viên hoàn thiện mã để tạo các hệ thống và mô phỏng chẩn đoán
    // 1. Tạo các hệ thống: Engine, TransmissionSystem, BrakeSystem
    // 2. Tạo DiagnosticSystem và thêm các hệ thống vào
    // 3. Mô phỏng các tình huống khác nhau:
    //    - Khởi động động cơ và chạy ở nhiều RPM
    //    - Thay đổi cấp số
    //    - Sử dụng phanh
    //    - Chạy chẩn đoán và hiển thị kết quả
    //    - Xóa mã lỗi và kiểm tra lại
    
    return 0;
}
