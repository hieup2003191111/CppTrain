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
