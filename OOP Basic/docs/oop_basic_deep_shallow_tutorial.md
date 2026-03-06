# Tài liệu giảng dạy: OOP Cơ bản trong C++ và Shallow Copy vs Deep Copy

**Mục tiêu:** Học viên hiểu được các khái niệm cơ bản của OOP trong C++ và sự khác biệt giữa Shallow Copy và Deep Copy, áp dụng vào thực tế.

## Hướng dẫn tự học
- **Cách sử dụng tài liệu:** Đọc từng phần theo thứ tự, chạy code ví dụ trên máy tính của bạn để kiểm tra kết quả. Sau mỗi phần, làm bài tập để củng cố kiến thức.
- **Yêu cầu kiến thức nền:** Biết cơ bản về C++ (biến, hàm, con trỏ).
- **Công cụ cần thiết:** Trình biên dịch C++ (g++), IDE như VS Code hoặc Visual Studio.
- **Cách kiểm tra:** Sau mỗi ví dụ, dự đoán kết quả trước khi chạy, so sánh với thực tế.
- **Tài liệu bổ sung:** Xem các file sample trong thư mục docs (sample_deep_shallow.cpp, sample_sensor_deepcopy.cpp, v.v.).

---

## Phần 1: Giới thiệu OOP trong C++

### 1.1 Khái niệm OOP (Object-Oriented Programming)
- OOP là phương pháp lập trình dựa trên đối tượng, giúp tổ chức code dễ quản lý hơn so với lập trình thủ tục.
- 4 nguyên tắc chính: 
  - **Encapsulation:** Bao bọc dữ liệu và phương thức trong class.
  - **Inheritance:** Kế thừa thuộc tính từ class cha.
  - **Polymorphism:** Một phương thức có thể có nhiều hình thức.
  - **Abstraction:** Ẩn chi tiết triển khai, chỉ hiển thị giao diện.

**Giải thích cụ thể:** OOP giúp mô phỏng thế giới thực, ví dụ: Một chiếc xe (object) có thuộc tính như màu sắc, tốc độ, và hành động như chạy.

### 1.2 Class và Object
- **Class:** Mẫu thiết kế cho đối tượng, định nghĩa thuộc tính và phương thức.
- **Object:** Thể hiện cụ thể của class, có giá trị riêng cho từng thuộc tính.

**Ví dụ chi tiết:**
```cpp
class Car {
public:
    std::string brand;  // Thuộc tính
    int year;
    void drive() {      // Phương thức
        std::cout << "Driving " << brand << std::endl;
    }
};

int main() {
    Car myCar;          // Tạo object
    myCar.brand = "Toyota";  // Gán giá trị
    myCar.year = 2020;
    myCar.drive();      // Gọi phương thức
    return 0;
}
```
**Giải thích:** Class `Car` định nghĩa mẫu, `myCar` là object cụ thể. Khi chạy, sẽ in "Driving Toyota".

**Câu hỏi tự kiểm tra:** Class khác gì với object? Tại sao cần class?

### 1.3 Constructor và Destructor
- **Constructor:** Hàm đặc biệt chạy khi tạo object, dùng để khởi tạo.
- **Destructor:** Hàm đặc biệt chạy khi object bị hủy, dùng để giải phóng tài nguyên.

**Ví dụ chi tiết:**
```cpp
class Car {
public:
    Car() { std::cout << "Car created" << std::endl; }  // Constructor
    ~Car() { std::cout << "Car destroyed" << std::endl; } // Destructor
};
```
**Giải thích:** Constructor không có kiểu trả về, tên giống class. Destructor có dấu ~. Khi tạo object, constructor chạy; khi kết thúc hàm, destructor chạy.

**Câu hỏi tự kiểm tra:** Khi nào constructor và destructor được gọi?

### 1.4 Encapsulation
- Bảo vệ dữ liệu bằng từ khóa private/public, chỉ truy cập qua phương thức public.

**Ví dụ chi tiết:**
```cpp
class Car {
private:
    int speed;  // Riêng tư
public:
    void setSpeed(int s) { speed = s; }  // Phương thức public
    int getSpeed() { return speed; }
};
```
**Giải thích:** Dữ liệu `speed` chỉ thay đổi qua `setSpeed`, đảm bảo an toàn.

**Câu hỏi tự kiểm tra:** Tại sao cần encapsulation?

### 1.5 Inheritance
- Kế thừa từ class cha, con class có thuộc tính và phương thức của cha.

**Ví dụ chi tiết:**
```cpp
class Vehicle {
public:
    void move() { std::cout << "Moving" << std::endl; }
};

class Car : public Vehicle {  // Kế thừa
public:
    void honk() { std::cout << "Honk!" << std::endl; }
};
```
**Giải thích:** `Car` kế thừa `move()` từ `Vehicle`, có thể dùng `myCar.move()`.

**Câu hỏi tự kiểm tra:** Lợi ích của inheritance là gì?

### 1.6 Polymorphism
- Đa hình: Phương thức cha có thể được ghi đè (override) bởi con.

**Ví dụ chi tiết:**
```cpp
class Vehicle {
public:
    virtual void move() { std::cout << "Vehicle moving" << std::endl; }
};

class Car : public Vehicle {
public:
    void move() override { std::cout << "Car moving" << std::endl; }
};
```
**Giải thích:** Từ khóa `virtual` cho phép ghi đè. Khi gọi qua con trỏ cha, sẽ chạy phương thức con.

**Câu hỏi tự kiểm tra:** Polymorphism khác gì với inheritance?

**Thời gian: 45 phút**  
**Bài tập:** Tạo class `Animal` với inheritance từ `LivingThing`, thêm constructor, destructor, và polymorphism. Chạy code và giải thích kết quả.

---

## Phần 2: Shallow Copy vs Deep Copy

### 2.1 Khái niệm
- **Shallow Copy:** Sao chép địa chỉ con trỏ, không sao chép dữ liệu thực. Hai object dùng chung vùng nhớ.
- **Deep Copy:** Sao chép toàn bộ dữ liệu, bao gồm vùng nhớ động. Mỗi object có vùng nhớ riêng.

**Giải thích cụ thể:** Shallow copy nhanh nhưng nguy hiểm với con trỏ. Deep copy an toàn nhưng tốn bộ nhớ.

### 2.2 Ví dụ cơ bản

**Ví dụ chi tiết:**
```cpp
#include <iostream>
#include <cstring>

class Shallow {
public:
    char* data;
    Shallow(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    Shallow(const Shallow& other) {
        data = other.data; // Shallow copy: chỉ copy địa chỉ
    }
    ~Shallow() { delete[] data; }
};

class Deep {
public:
    char* data;
    Deep(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    Deep(const Deep& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data); // Deep copy: copy dữ liệu
    }
    ~Deep() { delete[] data; }
};

int main() {
    Shallow s1("Hello");
    Shallow s2 = s1; // Shallow
    strcpy(s2.data, "World");
    std::cout << "s1: " << s1.data << std::endl; // Thay đổi theo s2

    Deep d1("Hello");
    Deep d2 = d1; // Deep
    strcpy(d2.data, "World");
    std::cout << "d1: " << d1.data << std::endl; // Không thay đổi
    return 0;
}
```
**Giải thích:** Với shallow, `s1.data` và `s2.data` cùng trỏ đến một vùng nhớ, thay đổi `s2` ảnh hưởng `s1`. Với deep, mỗi object có vùng nhớ riêng.

**Câu hỏi tự kiểm tra:** Tại sao shallow copy có thể gây lỗi?

### 2.3 Khi nào dùng Deep Copy?
- Khi class có con trỏ hoặc quản lý tài nguyên động (heap).
- Tránh lỗi double free (giải phóng cùng vùng nhớ 2 lần), dangling pointer (con trỏ treo).

**Giải thích cụ thể:** Trong ứng dụng lớn, shallow copy có thể dẫn đến crash hoặc dữ liệu sai.

### 2.4 Operator=
- Cần overload operator= cho deep copy để tránh shallow khi gán.

**Ví dụ chi tiết:**
```cpp
Deep& operator=(const Deep& other) {
    if (this != &other) {  // Tránh tự gán
        delete[] data;     // Giải phóng cũ
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);  // Copy mới
    }
    return *this;
}
```
**Giải thích:** Kiểm tra self-assignment, giải phóng bộ nhớ cũ trước khi copy mới.

**Câu hỏi tự kiểm tra:** Tại sao cần overload operator=?

**Bài tập:** Viết class `String` với deep copy constructor và operator=. Test với gán và copy.

---

## Phần 3: Ứng dụng thực tế trong ô tô (45 phút)

### 3.1 Ví dụ: Quản lý cảm biến
- Cảm biến có dữ liệu động: tên (string), giá trị (mảng float).

**Ví dụ chi tiết:**
```cpp
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
```
**Giải thích:** Constructor cấp phát động, deep copy sao chép toàn bộ, destructor giải phóng.

### 3.2 Ứng dụng với các module điều khiển
- EngineControl, ABSControl, AirConditionerControl nhận bản sao cảm biến.

**Ví dụ chi tiết:**
```cpp
class EngineControl {
public:
    SensorData sensor;
    EngineControl(const SensorData& s) : sensor(s) {}  // Deep copy
    void update() { sensor.values[0] += 10; }  // Thay đổi bản sao
};
```
**Giải thích:** Mỗi module có bản sao riêng, thao tác không ảnh hưởng lẫn nhau.

### 3.3 ECU (Electronic Control Unit) - Bộ điều khiển điện tử
- **ECU là gì?** ECU là bộ xử lý trung tâm trong xe ô tô, quản lý các hệ thống như động cơ, phanh, điều hòa. Nó nhận dữ liệu từ cảm biến, xử lý, và gửi lệnh đến các module.
- **Vai trò:** Đảm bảo an toàn, hiệu suất, và tiết kiệm nhiên liệu. ECU sử dụng OOP để tổ chức code, và deep copy để sao chép dữ liệu cảm biến an toàn.

**Ví dụ chi tiết: Class ECU quản lý các module**
```cpp
class ECU {
public:
    SensorData mainSensor;  // Cảm biến chính
    EngineControl engine;
    ABSControl abs;
    AirConditionerControl ac;

    ECU(const SensorData& s) : mainSensor(s), engine(s), abs(s), ac(s) {}  // Deep copy cho tất cả

    void process() {
        engine.update();  // Xử lý động cơ
        abs.update();     // Xử lý ABS
        ac.update();      // Xử lý điều hòa
        // mainSensor không bị thay đổi
    }
};
```
**Giải thích:** ECU nhận dữ liệu cảm biến qua deep copy, đảm bảo các module thao tác trên bản sao riêng. Điều này tránh xung đột dữ liệu và lỗi trong hệ thống thời gian thực.

**Câu hỏi tự kiểm tra:** ECU khác gì với các module điều khiển? Tại sao deep copy quan trọng trong ECU?

**Câu hỏi tự kiểm tra:** Tại sao deep copy quan trọng trong hệ thống ô tô?

**Thời gian: 45 phút**  
**Bài tập:** Tạo hệ thống cảm biến với 3 module điều khiển, sử dụng deep copy. Chạy và quan sát kết quả. Mở rộng với class ECU quản lý tất cả.

---

## Phần 4: Ôn tập và Q&A 
- Tổng kết: OOP giúp tổ chức code, deep copy đảm bảo an toàn với con trỏ.
- Thảo luận câu hỏi: Nếu có thắc mắc, ghi chú và hỏi.

**Tổng thời gian: 3 tiếng**

**Tài liệu bổ sung:** Xem các file sample trong thư mục docs (sample_deep_shallow.cpp, sample_sensor_deepcopy.cpp, sample_sensor_control_full.cpp).
