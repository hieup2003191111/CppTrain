# Singleton Design Pattern - Giải Thích Chi Tiết

## 1. Singleton là gì?

**Singleton** là một **Design Pattern** (mẫu thiết kế) thuộc nhóm **Creational Patterns** (mẫu khởi tạo). Mục đích của Singleton là:

- **Đảm bảo một class chỉ có DUY NHẤT MỘT instance (đối tượng)** trong suốt vòng đời của chương trình
- **Cung cấp một điểm truy cập toàn cục** (global access point) đến instance đó

## 2. Khi nào sử dụng Singleton?

### Các trường hợp phổ biến:

| Use Case | Giải thích |
|----------|------------|
| **Logger** | Chỉ cần một đối tượng ghi log cho toàn bộ ứng dụng |
| **Configuration Manager** | Quản lý cấu hình hệ thống tập trung |
| **Database Connection Pool** | Quản lý kết nối database |
| **Hardware Interface** | Giao tiếp với phần cứng (UART, SPI, I2C trong embedded) |
| **Cache Manager** | Quản lý bộ nhớ đệm |
| **Thread Pool** | Quản lý nhóm thread |

### Trong Embedded/AUTOSAR:

- **ECU State Manager**: Quản lý trạng thái ECU
- **Communication Manager**: Quản lý giao tiếp CAN/LIN
- **Diagnostic Event Manager**: Quản lý sự kiện chẩn đoán

## 3. Cấu trúc cơ bản

```
┌─────────────────────────────────────────┐
│              Singleton                   │
├─────────────────────────────────────────┤
│ - static instance: Singleton*           │  ← Biến static lưu instance duy nhất
│ - data: ...                             │  ← Dữ liệu của singleton
├─────────────────────────────────────────┤
│ - Singleton()                           │  ← Constructor PRIVATE
│ - ~Singleton()                          │  ← Destructor PRIVATE
│ + static getInstance(): Singleton&      │  ← Phương thức truy cập public
│ + doSomething(): void                   │  ← Các phương thức khác
└─────────────────────────────────────────┘
```

## 4. Các thành phần chính

### 4.1 Private Constructor
```cpp
private:
    Singleton() { /* khởi tạo */ }
```
→ Ngăn chặn việc tạo đối tượng từ bên ngoài class

### 4.2 Delete Copy Constructor & Assignment Operator
```cpp
Singleton(const Singleton&) = delete;
Singleton& operator=(const Singleton&) = delete;
```
→ Ngăn chặn việc copy đối tượng

### 4.3 Static Instance
```cpp
static Singleton* instance;  // hoặc
static Singleton& getInstance();
```
→ Lưu trữ instance duy nhất

### 4.4 Public Static Method (getInstance)
```cpp
public:
    static Singleton& getInstance() {
        static Singleton instance;  // Meyers' Singleton
        return instance;
    }
```
→ Điểm truy cập duy nhất đến instance

## 5. Các cách implement Singleton

### 5.1 Eager Initialization (Khởi tạo sớm)
- Instance được tạo ngay khi chương trình bắt đầu
- Đơn giản, thread-safe
- Tốn bộ nhớ nếu không dùng đến

### 5.2 Lazy Initialization (Khởi tạo trễ)
- Instance chỉ được tạo khi gọi `getInstance()` lần đầu
- Tiết kiệm bộ nhớ
- Cần xử lý thread-safety

### 5.3 Meyers' Singleton (Được khuyến nghị từ C++11)
- Sử dụng static local variable
- Thread-safe theo chuẩn C++11
- Đơn giản và an toàn

## 6. Thread Safety

### Vấn đề Race Condition:
```
Thread A: if (instance == nullptr)  ←── Cả hai thread
Thread B: if (instance == nullptr)  ←── kiểm tra cùng lúc
Thread A: instance = new Singleton();
Thread B: instance = new Singleton(); ← Tạo 2 instance!
```

### Giải pháp:
1. **Meyers' Singleton** (C++11+): Tự động thread-safe
2. **Double-Checked Locking**: Dùng mutex
3. **std::call_once**: Đảm bảo chỉ khởi tạo một lần

## 7. Ưu điểm và Nhược điểm

### ✅ Ưu điểm:
- Đảm bảo chỉ có một instance
- Truy cập toàn cục dễ dàng
- Khởi tạo trễ (lazy initialization) tiết kiệm tài nguyên
- Kiểm soát được việc tạo đối tượng

### ❌ Nhược điểm:
- Vi phạm **Single Responsibility Principle** (class vừa làm việc của nó, vừa quản lý instance)
- Khó unit test (khó mock/stub)
 - Có thể gây hidden dependencies
- Khó debug trong multi-threaded
- Lifetime management phức tạp

## 8. Best Practices

1. **Sử dụng Meyers' Singleton** cho C++11 trở lên
2. **Tránh lạm dụng** - chỉ dùng khi thực sự cần
3. **Cân nhắc Dependency Injection** thay thế
4. **Đảm bảo thread-safety** trong môi trường đa luồng
5. **Document rõ ràng** về lifetime và dependencies

## 9. Singleton vs Global Variable

| Tiêu chí | Singleton | Global Variable |
|----------|-----------|-----------------|
| Khởi tạo | Controlled, có thể lazy | Uncontrolled |
| Thread-safety | Có thể implement | Không |
| Inheritance | Có thể | Không |
| Interface | Có thể abstract | Không |
| Testability | Khó nhưng có thể | Rất khó |
