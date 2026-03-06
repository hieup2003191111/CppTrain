# Bố Cục Bộ Nhớ Của Class Trong C++ (So Sánh Với Struct)

## Giới Thiệu

Trong ngôn ngữ lập trình C++, **class** và **struct** có nhiều điểm tương đồng về bố cục bộ nhớ, nhưng chúng khác nhau về mặt ngữ nghĩa và một số tính năng liên quan đến kế thừa và đa hình. Bài viết này sẽ phân tích chi tiết bố cục bộ nhớ của class, so sánh với struct, và đi sâu vào các yếu tố ảnh hưởng như virtual functions, RTTI, dữ liệu tĩnh, và các kỹ thuật tối ưu hóa bộ nhớ.

## Sự Khác Biệt Cơ Bản Giữa Class và Struct

- **Class**: Mặc định các thành viên là `private`, được thiết kế cho lập trình hướng đối tượng với tính năng kế thừa và đa hình.
- **Struct**: Mặc định các thành viên là `public`, thường dùng cho cấu trúc dữ liệu đơn giản, nhưng cũng hỗ trợ kế thừa và đa hình.

Về bố cục bộ nhớ, cả hai đều tuân theo quy tắc tương tự: các thành viên được sắp xếp theo thứ tự khai báo, với padding để đảm bảo alignment. Tuy nhiên, khi có kế thừa và đa hình, class thường có thêm overhead từ virtual function table (vtable) và RTTI.

## Các Yếu Tố Ảnh Hưởng Đến Bố Cục Bộ Nhớ

### 1. Virtual Function Table Pointers (vptr)

Khi một class có ít nhất một virtual function, compiler sẽ thêm một con trỏ ẩn (vptr) vào đầu object. Con trỏ này trỏ đến virtual function table (vtable), chứa địa chỉ của các virtual functions.

```cpp
class Base {
public:
    virtual void func() { std::cout << "Base::func" << std::endl; }
    int data;
};

class Derived : public Base {
public:
    void func() override { std::cout << "Derived::func" << std::endl; }
    int derivedData;
};
```

**Bố cục bộ nhớ (giả định 64-bit):**
- Base object: [vptr (8 bytes)] [data (4 bytes)] [padding (4 bytes)]
- Derived object: [vptr (8 bytes)] [data (4 bytes)] [derivedData (4 bytes)] [padding (0 bytes)]

Struct không có virtual functions nên không có vptr.

### 2. Thông Tin RTTI (Runtime Type Information)

RTTI bao gồm thông tin về kiểu của object tại runtime, như `typeid` và `dynamic_cast`. Thông tin này thường được lưu trong vtable hoặc một cấu trúc riêng.

```cpp
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

void checkType(Base* obj) {
    std::cout << typeid(*obj).name() << std::endl;  // Sử dụng RTTI
}
```

RTTI thêm overhead nhỏ vào mỗi class có virtual functions.

### 3. Dữ liệu Tĩnh Của Class

Dữ liệu tĩnh (static members) không được lưu trong mỗi object, mà được chia sẻ toàn cục. Chúng không ảnh hưởng đến kích thước của từng object.

```cpp
class MyClass {
public:
    static int staticData;  // Không chiếm bộ nhớ trong object
    int instanceData;
};
```

**Bố cục:** Chỉ [instanceData (4 bytes)], staticData được lưu ở data segment.

### 4. Các Biến Thành Viên Thêm Vào Từ Lớp Cơ Sở

Khi kế thừa, các biến thành viên từ base class được thêm vào đầu bố cục của derived class.

```cpp
class Base {
    int baseData;
};

class Derived : public Base {
    int derivedData;
};
```

**Bố cục:** [baseData (4 bytes)] [derivedData (4 bytes)]

### 5. Padding Do Quy Tắc Kế Thừa và Đa Hình

Padding xảy ra để đảm bảo alignment. Với đa hình, vptr ở đầu có thể tạo thêm padding.

```cpp
class Base {
    char c;  // 1 byte
    virtual void func() {}
};

class Derived : public Base {
    int i;  // 4 bytes
};
```

**Bố cục (64-bit):**
- Base: [vptr (8)] [c (1)] [padding (7)] = 16 bytes
- Derived: [vptr (8)] [c (1)] [padding (3)] [i (4)] = 16 bytes

### 6. Object Pool Pattern

Object Pool là pattern để tái sử dụng objects thay vì tạo/xóa liên tục, cải thiện hiệu suất và giảm fragmentation.

```cpp
#include <vector>
#include <memory>

template<typename T>
class ObjectPool {
private:
    std::vector<std::unique_ptr<T>> pool;
    std::vector<T*> available;

public:
    T* acquire() {
        if (available.empty()) {
            pool.push_back(std::make_unique<T>());
            return pool.back().get();
        }
        T* obj = available.back();
        available.pop_back();
        return obj;
    }

    void release(T* obj) {
        available.push_back(obj);
    }
};
```

### 7. Cache Locality: Structure of Arrays (SoA)

Để cải thiện cache locality, thay vì Array of Structures (AoS), sử dụng Structure of Arrays (SoA).

**AoS (Array of Structures):**
```cpp
struct Particle {
    float x, y, z;
    float vx, vy, vz;
};

std::vector<Particle> particles(1000);
```

**SoA (Structure of Arrays):**
```cpp
struct Particles {
    std::vector<float> x, y, z;
    std::vector<float> vx, vy, vz;
};

Particles particles;
particles.x.resize(1000);
particles.y.resize(1000);
// ... tương tự cho các vector khác
```

**Ví dụ code hoàn chỉnh cho SoA:**

```cpp
#include <vector>
#include <iostream>
#include <chrono>

struct Particles_SoA {
    std::vector<float> x, y, z;
    std::vector<float> vx, vy, vz;
    std::vector<float> mass;

    void resize(size_t n) {
        x.resize(n);
        y.resize(n);
        z.resize(n);
        vx.resize(n);
        vy.resize(n);
        vz.resize(n);
        mass.resize(n);
    }

    size_t size() const { return x.size(); }
};

void updateParticles(Particles_SoA& particles, float dt) {
    for (size_t i = 0; i < particles.size(); ++i) {
        particles.x[i] += particles.vx[i] * dt;
        particles.y[i] += particles.vy[i] * dt;
        particles.z[i] += particles.vz[i] * dt;
    }
}

int main() {
    Particles_SoA particles;
    particles.resize(1000000);

    // Khởi tạo dữ liệu
    for (size_t i = 0; i < particles.size(); ++i) {
        particles.x[i] = static_cast<float>(i);
        particles.y[i] = static_cast<float>(i * 2);
        particles.z[i] = static_cast<float>(i * 3);
        particles.vx[i] = 1.0f;
        particles.vy[i] = 2.0f;
        particles.vz[i] = 3.0f;
        particles.mass[i] = 1.0f;
    }

    auto start = std::chrono::high_resolution_clock::now();
    updateParticles(particles, 0.01f);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Update time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    return 0;
}
```

SoA cải thiện cache locality vì các giá trị cùng loại được lưu liên tiếp, giảm cache misses.

## Ví Dụ Cụ Thể Trong ECU (Electronic Control Unit)

Để minh họa các khái niệm trên trong ngữ cảnh thực tế của hệ thống ECU trong ô tô, chúng ta sẽ sử dụng các class ECU có sẵn như `ECU` (lớp cơ sở), `EngineECU`, và `TransmissionECU`.

### 1. Virtual Function Table Pointers Trong ECU

Class `ECU` có virtual functions như `readSensors()`, `processData()`, v.v., nên có vptr.

```cpp
#include "ECU.h"
#include "EngineECU.h"

int main() {
    ECU* ecu = new EngineECU("ENG001");
    ecu->powerOn();        // Gọi qua vtable
    ecu->readSensors();    // Gọi qua vtable
    delete ecu;
    return 0;
}
```

**Bố cục bộ nhớ EngineECU object:**
- [vptr (8 bytes)] [id (string ~32 bytes)] [name (string ~32 bytes)] [isActive (1 byte)] [dtcCodes (vector ~24 bytes)] [engineTemperature (8)] [engineRPM (8)] [throttlePosition (8)] [fuelInjectionTime (8)] + padding

### 2. RTTI Trong ECU

Sử dụng RTTI để xác định loại ECU tại runtime.

```cpp
#include <typeinfo>
#include "ECU.h"
#include "EngineECU.h"
#include "TransmissionECU.h"  // Giả sử có class này

void identifyECU(ECU* ecu) {
    if (typeid(*ecu) == typeid(EngineECU)) {
        std::cout << "Đây là EngineECU" << std::endl;
    } else if (typeid(*ecu) == typeid(TransmissionECU)) {
        std::cout << "Đây là TransmissionECU" << std::endl;
    }
}

int main() {
    ECU* ecu1 = new EngineECU("ENG001");
    ECU* ecu2 = new TransmissionECU("TRM001");  // Giả sử có
    identifyECU(ecu1);
    identifyECU(ecu2);
    delete ecu1;
    delete ecu2;
    return 0;
}
```

### 3. Dữ liệu Tĩnh Trong ECU

Thêm dữ liệu tĩnh để theo dõi số lượng ECU instances.

```cpp
class ECU {
    // ... existing code ...
    static int totalECUs;  // Đếm tổng số ECU
public:
    ECU(const std::string& ecuId, const std::string& ecuName) {
        // ... existing code ...
        totalECUs++;
    }
    static int getTotalECUs() { return totalECUs; }
};

int ECU::totalECUs = 0;  // Khởi tạo static member

int main() {
    EngineECU* eng = new EngineECU("ENG001");
    std::cout << "Tổng số ECU: " << ECU::getTotalECUs() << std::endl;  // 1
    delete eng;
    return 0;
}
```

### 4. Biến Thành Viên Từ Lớp Cơ Sở Trong ECU

`EngineECU` kế thừa các biến từ `ECU`: `id`, `name`, `isActive`, `dtcCodes`.

```cpp
EngineECU eng("ENG001");
// Bố cục: [vptr] [id] [name] [isActive] [dtcCodes] [engineTemperature] [engineRPM] [throttlePosition] [fuelInjectionTime]
```

### 5. Padding Trong ECU

Với các biến double (8 bytes) và string, padding có thể xảy ra.

```cpp
class EngineECU : public ECU {
    double engineTemperature;  // 8 bytes
    char statusFlag;           // 1 byte -> padding 7 bytes
    double engineRPM;          // 8 bytes
    // Tổng: ~80+ bytes với padding
};
```

### 6. Object Pool Pattern Cho ECU

Tái sử dụng ECU objects để tránh tạo/xóa liên tục.

```cpp
#include <vector>
#include <memory>
#include "ECU.h"
#include "EngineECU.h"

template<typename T>
class ECUObjectPool {
private:
    std::vector<std::unique_ptr<T>> pool;
    std::vector<T*> available;

public:
    T* acquire() {
        if (available.empty()) {
            pool.push_back(std::make_unique<T>("POOL_ECU"));
            return pool.back().get();
        }
        T* obj = available.back();
        available.pop_back();
        return obj;
    }

    void release(T* obj) {
        obj->powerOff();
        available.push_back(obj);
    }
};

int main() {
    ECUObjectPool<EngineECU> pool;
    EngineECU* ecu1 = pool.acquire();
    ecu1->powerOn();
    // Sử dụng ecu1
    pool.release(ecu1);
    
    EngineECU* ecu2 = pool.acquire();  // Tái sử dụng
    return 0;
}
```

### 7. Structure of Arrays Cho Cảm Biến ECU

Áp dụng SoA cho nhiều cảm biến ECU để cải thiện cache locality.

```cpp
#include <vector>

struct ECUSensors_SoA {
    std::vector<double> temperatures;
    std::vector<double> rpms;
    std::vector<double> throttlePositions;
    std::vector<std::string> ecuIds;

    void resize(size_t n) {
        temperatures.resize(n);
        rpms.resize(n);
        throttlePositions.resize(n);
        ecuIds.resize(n);
    }

    size_t size() const { return temperatures.size(); }
};

void updateECUSensors(ECUSensors_SoA& sensors, double dt) {
    for (size_t i = 0; i < sensors.size(); ++i) {
        // Cập nhật nhiệt độ dựa trên RPM
        sensors.temperatures[i] += sensors.rpms[i] * 0.001 * dt;
        // Cập nhật throttle
        sensors.throttlePositions[i] = std::min(100.0, sensors.throttlePositions[i] + 1.0);
    }
}

int main() {
    ECUSensors_SoA sensors;
    sensors.resize(1000);
    
    // Khởi tạo
    for (size_t i = 0; i < sensors.size(); ++i) {
        sensors.temperatures[i] = 80.0 + i * 0.1;
        sensors.rpms[i] = 2000.0 + i * 10;
        sensors.throttlePositions[i] = 50.0;
        sensors.ecuIds[i] = "ECU_" + std::to_string(i);
    }
    
    updateECUSensors(sensors, 0.1);
    return 0;
}
```

Các ví dụ này cho thấy cách áp dụng các khái niệm bố cục bộ nhớ vào hệ thống ECU thực tế, giúp tối ưu hóa hiệu suất và quản lý tài nguyên hiệu quả.

## Kết Luận

Bố cục bộ nhớ của class trong C++ phức tạp hơn struct khi có kế thừa và đa hình, với overhead từ vptr, RTTI, và padding. Hiểu rõ các yếu tố này giúp tối ưu hóa hiệu suất và sử dụng bộ nhớ hiệu quả. Các pattern như Object Pool và kỹ thuật SoA có thể cải thiện đáng kể hiệu suất trong các ứng dụng đòi hỏi hiệu năng cao.