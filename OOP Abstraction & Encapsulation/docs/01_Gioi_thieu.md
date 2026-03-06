# Giới thiệu về Abstraction và Encapsulation trong OOP

## Abstraction (Trừu tượng hóa)

**Abstraction** là việc xác định các đặc điểm thiết yếu của một đối tượng và bỏ qua các chi tiết không cần thiết. Nó giúp giảm độ phức tạp bằng cách che giấu các chi tiết triển khai và chỉ hiển thị chức năng cần thiết cho người dùng.

### Cách thể hiện Abstraction trong C++:
1. **Abstract Classes**: Sử dụng các lớp trừu tượng với phương thức thuần ảo (pure virtual)
2. **Interfaces**: Được thực hiện thông qua các lớp trừu tượng chỉ chứa phương thức thuần ảo

### Ví dụ:
```cpp
// Lớp trừu tượng
class Vehicle {
public:
    virtual void start() = 0;  // Phương thức thuần ảo
    virtual void stop() = 0;   // Phương thức thuần ảo
    virtual ~Vehicle() {} // Destructor ảo
};

// Lớp cụ thể kế thừa từ lớp trừu tượng
class Car : public Vehicle {
public:
    void start() override {
        cout << "Car started" << endl;
    }
    void stop() override {
        cout << "Car stopped" << endl;
    }
};
```

## Encapsulation (Đóng gói)

**Encapsulation** là việc gói dữ liệu và các phương thức thao tác với dữ liệu đó vào trong một đơn vị duy nhất (class) và hạn chế truy cập trực tiếp đến một số thành phần. Nó giúp bảo vệ dữ liệu khỏi sự can thiệp không mong muốn.

### Cách thể hiện Encapsulation trong C++:
1. **Access Specifiers**: public, private, protected
2. **Getters/Setters**: Phương thức truy cập và thiết lập dữ liệu

### Ví dụ:
```cpp
class Engine {
private:
    // Dữ liệu được bảo vệ
    bool isRunning;
    int rpm;
    float temperature;

public:
    // Constructor
    Engine() : isRunning(false), rpm(0), temperature(0.0) {}
    
    // Getter methods
    bool getIsRunning() const { return isRunning; }
    int getRPM() const { return rpm; }
    float getTemperature() const { return temperature; }
    
    // Setter methods
    void setRPM(int newRPM) {
        if (newRPM >= 0 && newRPM <= 10000) {
            rpm = newRPM;
        }
    }
    
    // Functionality
    void start() {
        if (!isRunning) {
            isRunning = true;
            rpm = 800; // Idle RPM
        }
    }
    
    void stop() {
        isRunning = false;
        rpm = 0;
    }
};
```

## Lợi ích trong phát triển phần mềm ô tô

### Abstraction
- **Quản lý độ phức tạp**: Giúp quản lý các hệ thống phức tạp trong ô tô
- **Tái sử dụng**: Cho phép tạo các interface tiêu chuẩn có thể sử dụng trong nhiều mô hình xe
- **Dễ bảo trì**: Có thể thay đổi triển khai cụ thể mà không ảnh hưởng đến các thành phần khác

### Encapsulation
- **Bảo mật dữ liệu**: Bảo vệ dữ liệu quan trọng của xe (như thông số động cơ)
- **Kiểm soát truy cập**: Đảm bảo dữ liệu chỉ được thay đổi theo cách hợp lệ
- **Khả năng kiểm thử**: Dễ dàng kiểm thử từng thành phần một cách độc lập

## Ứng dụng trong phần mềm ô tô
1. **Hệ thống điều khiển động cơ (ECU)**
2. **Hệ thống thông tin giải trí**
3. **Hệ thống hỗ trợ lái xe (ADAS)**
4. **Hệ thống chẩn đoán và giám sát**
