// examples.cpp
// Ví dụ cụ thể để chạy: Arrays, Pointers (Basic & Advanced), References trong C++ cho ECU/MCU Autosar
#include <iostream>
#include <vector> // Cho std::vector trong ví dụ nâng cao
using namespace std;

// Ví dụ 1: Arrays Cơ Bản - Quản lý dữ liệu cảm biến
void array_basic_example() {
    cout << "\n--- Ví Dụ Arrays Cơ Bản: Dữ Liệu Cảm Biến ---\n";
    const int NUM_SENSORS = 5;
    float sensorData[NUM_SENSORS] = {23.5, 24.1, 22.8, 25.0, 23.9}; // Nhiệt độ cảm biến (°C)

    cout << "Dữ liệu cảm biến: ";
    for (int i = 0; i < NUM_SENSORS; ++i) {
        cout << sensorData[i] << "°C ";
    }
    cout << endl;

    // Tính trung bình
    float sum = 0;
    for (int i = 0; i < NUM_SENSORS; ++i) sum += sensorData[i];
    cout << "Nhiệt độ trung bình: " << sum / NUM_SENSORS << "°C" << endl;
}

// Ví dụ 2: Arrays Nâng Cao - Mảng Đa Chiều cho Ma Trận Dữ Liệu
void array_advanced_example() {
    cout << "\n--- Ví Dụ Arrays Nâng Cao: Ma Trận Dữ Liệu ECU ---\n";
    const int ROWS = 3, COLS = 4;
    int ecuMatrix[ROWS][COLS] = {
        {1, 2, 3, 4},   // Dòng 1: Dữ liệu từ ECU 1
        {5, 6, 7, 8},   // Dòng 2: Dữ liệu từ ECU 2
        {9, 10, 11, 12} // Dòng 3: Dữ liệu từ ECU 3
    };

    cout << "Ma trận dữ liệu ECU:\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << ecuMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Tìm giá trị lớn nhất
    int maxVal = ecuMatrix[0][0];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (ecuMatrix[i][j] > maxVal) maxVal = ecuMatrix[i][j];
        }
    }
    cout << "Giá trị lớn nhất: " << maxVal << endl;
}

// Ví dụ 3: Pointers Cơ Bản - Truy Cập Hardware Register
void pointer_basic_example() {
    cout << "\n--- Ví Dụ Pointers Cơ Bản: Truy Cập Hardware Register ---\n";
    int hardwareRegister = 0x1234; // Giả lập địa chỉ register
    int* regPtr = &hardwareRegister; // Con trỏ đến register

    cout << "Giá trị register ban đầu: 0x" << hex << *regPtr << endl;
    *regPtr = 0x5678; // Ghi giá trị mới (ví dụ: cấu hình hardware)
    cout << "Giá trị register sau khi ghi: 0x" << hex << *regPtr << endl;

    // Kiểm tra null (an toàn Autosar)
    int* nullPtr = nullptr;
    if (nullPtr == nullptr) {
        cout << "Con trỏ null được xử lý an toàn." << endl;
    }
}

// Ví dụ 4: Pointers Nâng Cao - Quản Lý Buffer UART với Pointer Arithmetic
void pointer_advanced_example() {
    cout << "\n--- Ví Dụ Pointers Nâng Cao: Buffer UART với Pointer Arithmetic ---\n";
    const int BUFFER_SIZE = 10;
    char uartBuffer[BUFFER_SIZE] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l'}; // Buffer nhận từ UART
    char* bufPtr = uartBuffer; // Con trỏ đến buffer

    cout << "Nội dung buffer: ";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cout << *(bufPtr + i); // Pointer arithmetic
    }
    cout << endl;

    // Sao chép dữ liệu bằng pointers
    char copyBuffer[BUFFER_SIZE];
    char* copyPtr = copyBuffer;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        *(copyPtr + i) = *(bufPtr + i);
    }
    cout << "Buffer sao chép: ";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cout << copyBuffer[i];
    }
    cout << endl;

    // Function pointer cho callback (Autosar RTE)
    void (*callback)(char*) = [](char* data) { cout << "Callback nhận: " << data << endl; };
    callback(uartBuffer);
}

// Ví dụ 5: References Cơ Bản - Alias cho Biến Cấu Hình
void reference_basic_example() {
    cout << "\n--- Ví Dụ References Cơ Bản: Alias cho Biến Cấu Hình ---\n";
    int configValue = 100; // Giá trị cấu hình ECU
    int& configRef = configValue; // Tham chiếu để dễ truy cập
    cout << "Giá trị cấu hình ban đầu: " << configValue << endl;
    configRef = 200; // Thay đổi qua tham chiếu
    cout << "Giá trị cấu hình sau thay đổi: " << configValue << endl;
}

// Ví dụ 6: References Nâng Cao - Truyền Tham Chiếu trong Hàm để Tối Ưu
void reference_advanced_example() {
    cout << "\n--- Ví Dụ References Nâng Cao: Truyền Tham Chiếu trong Hàm ---\n";
    struct SensorData {
        float temperature;
        int pressure;
    };

    SensorData sensor = {25.5, 1013};
    cout << "Dữ liệu cảm biến ban đầu: Temp=" << sensor.temperature << "°C, Pressure=" << sensor.pressure << " hPa" << endl;
    // Hàm cập nhật dữ liệu qua tham chiếu (tránh copy)
    auto updateSensor = [](SensorData& data, float newTemp, int newPress) {
        data.temperature = newTemp;
        data.pressure = newPress;
    };

    updateSensor(sensor, 26.0, 1015);
    cout << "Dữ liệu cảm biến sau cập nhật: Temp=" << sensor.temperature << "°C, Pressure=" << sensor.pressure << " hPa" << endl;

    // Const reference để đọc an toàn
    auto printSensor = [](const SensorData& data) {
        cout << "In dữ liệu: Temp=" << data.temperature << "°C, Pressure=" << data.pressure << " hPa" << endl;
    };
    printSensor(sensor);
}

int main() {
    cout << "Chạy Các Ví Dụ Cụ Thể cho Arrays, Pointers & References trong ECU/MCU Autosar\n";
    array_basic_example();
    array_advanced_example();
    pointer_basic_example();
    pointer_advanced_example();
    reference_basic_example();
    reference_advanced_example();
    cout << "\nHoàn thành tất cả ví dụ!" << endl;
    return 0;
}
