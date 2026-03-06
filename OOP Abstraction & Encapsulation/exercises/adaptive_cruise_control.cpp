// Bài tập thực hành: Hệ thống điều khiển hành trình thích ứng (Adaptive Cruise Control)
// Học viên hoàn thiện các lớp còn thiếu và phương thức được đánh dấu TODO

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Cấu trúc dữ liệu vị trí
struct Position {
    double x;  // mét - theo trục dọc (phía trước xe dương, phía sau âm)
    double y;  // mét - theo trục ngang (bên phải dương, bên trái âm)
    
    Position(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};

// Cấu trúc dữ liệu vận tốc
struct Velocity {
    double speed;     // m/s
    double heading;   // rad - góc hướng (0 là thẳng)
    
    Velocity(double _speed = 0.0, double _heading = 0.0) 
        : speed(_speed), heading(_heading) {}
};

// C ấu trúc dữ liệu trạng thái xe
struct VehicleState {
    Position position;  // Vị trí hiện tại
    Velocity velocity;  // Vận tốc hiện tại
    double acceleration;  // m/s^2 - gia tốc hiện tại
    bool cruiseEnabled;   // Trạng thái bật/tắt cruise control
    
    VehicleState() : acceleration(0.0), cruiseEnabled(false) {}
};

// Lớp trừu tượng cho cảm biến
class Sensor {
public:
    virtual void update() = 0;
    virtual bool isOperational() const = 0;
    virtual std::string getStatus() const = 0;
    virtual ~Sensor() {}
};
class SpeedSensor : public Sensor{
private:
    double currentSpeed;
    bool m_isOperational;
public:
    SpeedSensor(): currentSpeed(0.0),m_isOperational(true){}
    void update() override{
        m_isOperational = (rand() %100 >0);
    }
    bool isOperational() const override{
        return m_isOperational;
    }
    std::string getStatus() const override{
        return "Speed Sensor : " + std::to_string(currentSpeed)+"m/s (" +(m_isOperational?"Ok":"Fault")+")";
    }
    void updateSpeed(double speed){
        if(m_isOperational){
            currentSpeed=speed;
        }
        else{
            currentSpeed =0.0;
        }
    }
    double getSpeed() const{
        return currentSpeed;
    }

};

// Lớp cảm biến radar - phát hiện vật thể phía trước
class RadarSensor : public Sensor {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    bool operational;
    double maxRange;  // mét
    std::vector<Position> detectedObjects;
    
    // Giả lập dữ liệu radar
    void simulateDetection(const Position& vehiclePosition) {
        detectedObjects.clear();
        
        // Giả lập phát hiện vật thể phía trước ở khoảng cách ngẫu nhiên
        if (rand() % 10 > 2) {  // 70% khả năng có vật thể
            double distance = 10 + (rand() % 80); // 10-90 mét phía trước
            double lateralOffset = -1.5 + (rand() % 30) / 10.0; // -1.5 đến 1.5 mét theo chiều ngang
            
            detectedObjects.push_back(Position(vehiclePosition.x + distance, 
                                              vehiclePosition.y + lateralOffset));
        }
    }
    
public:
    RadarSensor(double range = 100.0) : operational(true), maxRange(range) {}
    
    void update() override {
        // Giả lập cập nhật trạng thái cảm biến
        operational = (rand() % 100 > 2); // 98% khả năng hoạt động bình thường
        
        if (!operational) {
            std::cout << "Radar sensor malfunction detected!" << std::endl;
        }
    }
    
    bool isOperational() const override {
        return operational;
    }
    
    std::string getStatus() const override {
        std::string status = "Radar Sensor:\n";
        status += "Status: " + std::string(operational ? "Operational" : "Fault") + "\n";
        status += "Range: " + std::to_string(maxRange) + " meters\n";
        status += "Detected Objects: " + std::to_string(detectedObjects.size()) + "\n";
        
        return status;
    }
    
    // Phương thức đặc thù cho cảm biến radar
    void detectObjects(const Position& vehiclePosition) {
        if (operational) {
            simulateDetection(vehiclePosition);
        } else {
            detectedObjects.clear();
        }
    }
    
    // Lấy vật thể gần nhất phía trước trong làn đường
    Position getClosestFrontObject(double laneWidth = 3.0) const {
        if (!operational || detectedObjects.empty()) {
            return Position(-1.0, -1.0); // Không có vật thể nào
        }
        
        Position closest(-1.0, -1.0);
        double minDistance = maxRange + 1.0;
        
        for (const auto& obj : detectedObjects) {
            // Chỉ xem xét vật thể trong làn đường (giới hạn theo chiều ngang)
            if (std::abs(obj.y) <= laneWidth / 2.0) {
                // Chỉ xem xét vật thể phía trước (x > 0)
                if (obj.x > 0 && obj.x < minDistance) {
                    minDistance = obj.x;
                    closest = obj;
                }
            }
        }
        
        return closest;
    }
};

// TODO: Học viên triển khai lớp cảm biến vận tốc SpeedSensor kế thừa từ Sensor
// Lớp này theo dõi vận tốc của xe


// Lớp điều khiển xe
class VehicleController {
private:
    VehicleState state;
    double maxAcceleration; // m/s^2
    double maxDeceleration; // m/s^2 (giá trị dương)
    double targetSpeed;     // m/s
    
public:
    VehicleController()
        : maxAcceleration(2.0), maxDeceleration(3.0), targetSpeed(0.0) {
        // Khởi tạo vị trí và vận tốc ban đầu
        state.position = Position(0.0, 0.0);
        state.velocity = Velocity(0.0, 0.0);
        state.acceleration = 0.0;
        state.cruiseEnabled = false;
    }
    
    void setTargetSpeed(double speed) {
        // Chuyển đổi từ km/h sang m/s nếu cần
        targetSpeed = speed;
        std::cout << "Target speed set to: " << speed << " m/s" << std::endl;
    }
    
    void accelerate(double amount) {
        if (amount > maxAcceleration) {
            amount = maxAcceleration;
        } else if (amount < -maxDeceleration) {
            amount = -maxDeceleration;
        }
        
        state.acceleration = amount;
        std::cout << "Vehicle " << (amount >= 0 ? "accelerating" : "decelerating") 
                  << " at " << std::abs(amount) << " m/s²" << std::endl;
    }
    
    void updateState(double deltaTime) {
        // Cập nhật vận tốc dựa trên gia tốc
        state.velocity.speed += state.acceleration * deltaTime;
        
        // Đảm bảo vận tốc không âm
        if (state.velocity.speed < 0) {
            state.velocity.speed = 0;
        }
        
        // Cập nhật vị trí dựa trên vận tốc
        state.position.x += state.velocity.speed * std::cos(state.velocity.heading) * deltaTime;
        state.position.y += state.velocity.speed * std::sin(state.velocity.heading) * deltaTime;
    }
    
    void enableCruiseControl() {
        state.cruiseEnabled = true;
        std::cout << "Cruise control enabled" << std::endl;
    }
    
    void disableCruiseControl() {
        state.cruiseEnabled = false;
        std::cout << "Cruise control disabled" << std::endl;
    }
    
    const VehicleState& getState() const {
        return state;
    }
    
    double getTargetSpeed() const {
        return targetSpeed;
    }
};
class AdaptiveCruiseControl{
private :
    RadarSensor* radar;
    SpeedSensor* speedSensor;
    VehicleController* controller;

    double safeDistance;
    double targetSpeed;
    bool isActive;

public:
    AdaptiveCruiseControl(RadarSensor* r,SpeedSensor* s,VehicleController* c)
        :radar(r),speedSensor(s),controller(c),
        safeDistance(20.0),targetSpeed(0.0),isActive(false){}

    void run(double deltaTime){
        if(!isActive) return;
        //check cam bien
        if (!radar->isOperational() || !speedSensor->isOperational()) {
            std::cout << "ACC Error: Sensor failure! Disabling system." << std::endl;
            isActive = false;
            controller->accelerate(0); // Dừng tác động ga
            return;
        }

        //lay du lieu
        Position leadVehicle = radar->getClosestFrontObject();
        double currentSpeed = speedSensor->getSpeed();

        //dieu khien
        if(leadVehicle.x > 0 && leadVehicle.x<safeDistance){
            controller->accelerate(-1.5);
        } else if(currentSpeed < targetSpeed){
            controller->accelerate(1);
        }
        else{
            controller->accelerate(0);
        }
        controller->updateState(deltaTime);
        speedSensor->updateSpeed(controller->getState().velocity.speed);

    }
    void setTarget(double s){
        targetSpeed =s;
        isActive=true;
    }
};
// TODO: Học viên triển khai lớp AdaptiveCruiseControl
// Lớp này sử dụng các cảm biến (RadarSensor, SpeedSensor) và VehicleController
// để điều khiển vận tốc xe và giữ khoảng cách an toàn với xe phía trước


// Hàm main - mô phỏng hoạt động của hệ thống
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // TODO: Tạo các đối tượng cần thiết và mô phỏng hoạt động của ACC
    // 1. Tạo các cảm biến (RadarSensor, SpeedSensor)
    RadarSensor radar(100.0);
    SpeedSensor speed;
    VehicleController controller;
    // 2. Tạo VehicleController
    AdaptiveCruiseControl acc(&radar,&speed,&controller );
    acc.setTarget(8.0);
    // 3. Tạo AdaptiveCruiseControl, truyền các cảm biến và controller
    // 4. Chạy mô phỏng với vòng lặp thời gian thực
    for(int i=0;i<10;++i){
        std::cout << "\n---step " <<i<<"---"<<std::endl;
        radar.update();
        radar.detectObjects(controller.getState().position);
        speed.update();
        acc.run(1.0);
        std::cout << speed.getStatus() << std::endl;
        std::cout << "Vehicle Position X: " << controller.getState().position.x << std::endl;       
    }
    //    - Cập nhật cảm biến
    //    - Cập nhật hệ thống ACC
    //    - Hiển thị trạng thái
    
    return 0;
}
