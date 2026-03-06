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
        sensor.values[0] += 10; // Giả sử động cơ tăng nhiệt độ
    }
};

class ABSControl {
public:
    SensorData sensor;
    ABSControl(const SensorData& s) : sensor(s) {}
    void update() {
        sensor.values[1] -= 5; // ABS giảm áp suất phanh
    }
};

class AirConditionerControl {
public:
    SensorData sensor;
    AirConditionerControl(const SensorData& s) : sensor(s) {}
    void update() {
        sensor.values[0] -= 2; // Điều hòa làm mát
    }
};

int main() {
    SensorData tempSensor("Temp+Pressure", 2, 30.0f);
    tempSensor.values[1] = 100.0f; // Giá trị thứ 2 là áp suất phanh

    EngineControl engine(tempSensor);
    ABSControl abs(tempSensor);
    AirConditionerControl ac(tempSensor);

    engine.update();
    abs.update();
    ac.update();

    std::cout << "Sensor gốc: " << tempSensor.values[0] << ", " << tempSensor.values[1] << std::endl;
    std::cout << "Sensor trong EngineControl: " << engine.sensor.values[0] << ", " << engine.sensor.values[1] << std::endl;
    std::cout << "Sensor trong ABSControl: " << abs.sensor.values[0] << ", " << abs.sensor.values[1] << std::endl;
    std::cout << "Sensor trong AirConditionerControl: " << ac.sensor.values[0] << ", " << ac.sensor.values[1] << std::endl;
    return 0;
}
