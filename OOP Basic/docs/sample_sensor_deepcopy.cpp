#include <iostream>
#include <cstring>

// Ví dụ: Quản lý thông tin cảm biến trong xe ô tô
class SensorData {
public:
    char* name;
    float* values;
    int size;
    // Constructor
    SensorData(const char* sensorName, int n, float initVal) : size(n) {
        name = new char[strlen(sensorName) + 1];
        strcpy(name, sensorName);
        values = new float[size];
        for (int i = 0; i < size; ++i) values[i] = initVal;
    }
    // Copy constructor (Deep Copy)
    SensorData(const SensorData& other) : size(other.size) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        values = new float[size];
        for (int i = 0; i < size; ++i) values[i] = other.values[i];
    }
    // Destructor
    ~SensorData() {
        delete[] name;
        delete[] values;
    }
    // Hiển thị thông tin
    void print() const {
        std::cout << "Sensor: " << name << ", Values: ";
        for (int i = 0; i < size; ++i) std::cout << values[i] << ' ';
        std::cout << std::endl;
    }
};

int main() {
    SensorData tempSensor("Temperature", 3, 25.0f);
    SensorData tempSensorCopy = tempSensor; // Deep copy
    tempSensor.values[0] = 100.0f; // Thay đổi giá trị cảm biến gốc
    std::cout << "Original: "; tempSensor.print();
    std::cout << "Copy:     "; tempSensorCopy.print();
    // tempSensorCopy không bị ảnh hưởng bởi thay đổi của tempSensor
    return 0;
}
