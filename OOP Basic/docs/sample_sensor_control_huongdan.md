# Hướng dẫn sử dụng Deep Copy với cảm biến và control trong ô tô

## 1. Vì sao cần Deep Copy với cảm biến?
Trong ứng dụng ô tô, dữ liệu cảm biến thường được lưu trữ động (con trỏ, mảng động). Nếu chỉ dùng shallow copy, khi copy đối tượng cảm biến, các module khác nhau (ví dụ: điều khiển động cơ, điều hòa, phanh ABS...) sẽ cùng truy cập và thay đổi chung một vùng nhớ, dễ gây lỗi hoặc xung đột dữ liệu.

Deep copy giúp mỗi module có bản sao dữ liệu riêng, tránh ảnh hưởng lẫn nhau.

## 2. Ví dụ: Deep Copy khi truyền dữ liệu cảm biến cho control

```cpp
#include <iostream>
#include <cstring>

class SensorData {
public:
    char* name;
    float* values;
    int size;
    SensorData(const char* sensorName, int n, float initVal) : size(n) {
        name = new char[strlen(sensorName) + 1];
        strcpy(name, sensorName);
        values = new float[size];
        for (int i = 0; i < size; ++i) values[i] = initVal;
    }
    // Deep copy
    SensorData(const SensorData& other) : size(other.size) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        values = new float[size];
        for (int i = 0; i < size; ++i) values[i] = other.values[i];
    }
    ~SensorData() {
        delete[] name;
        delete[] values;
    }
};

class EngineControl {
public:
    SensorData sensor;
    EngineControl(const SensorData& s) : sensor(s) {}
    void update() {
        // Giả sử điều khiển động cơ thay đổi giá trị cảm biến
        sensor.values[0] += 10;
    }
};

int main() {
    SensorData tempSensor("Temp", 2, 30.0f);
    EngineControl engine(tempSensor); // Deep copy
    engine.update();
    std::cout << "Sensor gốc: " << tempSensor.values[0] << std::endl;
    std::cout << "Sensor trong EngineControl: " << engine.sensor.values[0] << std::endl;
    // tempSensor không bị ảnh hưởng bởi thay đổi trong EngineControl
    return 0;
}
```

## 3. Kết luận
- Khi truyền dữ liệu cảm biến cho các module điều khiển, nên dùng deep copy để tránh xung đột dữ liệu.
- Mỗi module sẽ có vùng nhớ riêng, an toàn khi thao tác.


## 4. Ví dụ mở rộng: Deep Copy với ABS và Điều hòa

### a) Module ABS (chống bó cứng phanh)
```cpp
class ABSControl {
public:
    SensorData sensor;
    ABSControl(const SensorData& s) : sensor(s) {}
    void update() {
        // ABS xử lý dữ liệu cảm biến phanh
        sensor.values[1] -= 5;
    }
};

// Sử dụng trong main:
ABSControl abs(tempSensor); // Deep copy
abs.update();
std::cout << "Sensor trong ABSControl: " << abs.sensor.values[1] << std::endl;
```

### b) Module Điều hòa (Air Conditioner)
```cpp
class AirConditionerControl {
public:
    SensorData sensor;
    AirConditionerControl(const SensorData& s) : sensor(s) {}
    void update() {
        // Điều hòa điều chỉnh nhiệt độ dựa trên cảm biến
        sensor.values[0] -= 2;
    }
};

// Sử dụng trong main:
AirConditionerControl ac(tempSensor); // Deep copy
ac.update();
std::cout << "Sensor trong AirConditionerControl: " << ac.sensor.values[0] << std::endl;
```

## 5. Tổng kết
- Mỗi module (Engine, ABS, Điều hòa, ...) đều nhận bản sao dữ liệu cảm biến riêng nhờ deep copy.
- Thao tác của từng module không ảnh hưởng lẫn nhau, đảm bảo an toàn dữ liệu.
