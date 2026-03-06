# Bài tập thực hành: Bố cục bộ nhớ trong C/C++

## Bài 1: Phân tích bố cục bộ nhớ cơ bản

**Yêu cầu:**
1. Viết một chương trình C/C++ khai báo và sử dụng các loại biến khác nhau (toàn cục, cục bộ, tĩnh).
2. In ra địa chỉ của từng biến.
3. Phân tích và giải thích các vùng bộ nhớ mà mỗi biến thuộc về.
4. So sánh các địa chỉ để xác nhận hiểu biết về bố cục bộ nhớ.

**Template code:**

```cpp
#include <iostream>

// TODO: Khai báo biến toàn cục (khởi tạo và không khởi tạo)

void function1() {
    // TODO: Khai báo biến cục bộ và biến tĩnh
    
    // TODO: In ra địa chỉ của các biến
}

void function2() {
    // TODO: Khai báo biến cục bộ
    
    // TODO: In ra địa chỉ của các biến
    
    // TODO: Cấp phát động một số biến và in địa chỉ
}

int main() {
    // TODO: Gọi các hàm và phân tích kết quả
    return 0;
}
```

## Bài 2: Hiểu về Stack và đệ quy

**Yêu cầu:**
1. Viết một hàm đệ quy với các biến cục bộ.
2. In ra địa chỉ của các biến cục bộ trong mỗi lần gọi đệ quy.
3. Phân tích cách stack frame được tạo và giải phóng.
4. Thử nghiệm với số lần gọi đệ quy khác nhau và quan sát.

**Template code:**

```cpp
#include <iostream>

void recursiveFunction(int depth, int maxDepth) {
    // TODO: Khai báo một số biến cục bộ
    
    // TODO: In ra thông tin về độ sâu đệ quy hiện tại và địa chỉ của các biến
    
    // TODO: Điều kiện dừng đệ quy
    
    // TODO: Gọi đệ quy
}

int main() {
    int maxDepth;
    std::cout << "Nhập độ sâu tối đa cho đệ quy: ";
    std::cin >> maxDepth;
    
    recursiveFunction(1, maxDepth);
    
    return 0;
}
```

## Bài 3: Quản lý bộ nhớ động và memory leak

**Yêu cầu:**
1. Viết một chương trình tạo danh sách liên kết đơn.
2. Thêm và xóa phần tử trong danh sách.
3. Đảm bảo không có memory leak khi xóa các phần tử.
4. Sử dụng các công cụ như Valgrind (Linux) hoặc Visual Studio Memory Profiler (Windows) để kiểm tra memory leak.

**Template code:**

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() {
        // TODO: Khởi tạo danh sách
    }
    
    ~LinkedList() {
        // TODO: Giải phóng tất cả bộ nhớ trong destructor
    }
    
    void addNode(int value) {
        // TODO: Thêm một node mới vào danh sách
    }
    
    void removeNode(int value) {
        // TODO: Tìm và xóa node có giá trị cần tìm
        // Đảm bảo giải phóng bộ nhớ đúng cách
    }
    
    void display() {
        // TODO: Hiển thị tất cả các phần tử trong danh sách
    }
};

int main() {
    LinkedList list;
    
    // TODO: Thêm một số phần tử vào danh sách
    
    // TODO: Hiển thị danh sách
    
    // TODO: Xóa một số phần tử và kiểm tra memory leak
    
    return 0;
}
```

## Bài 4: Phân tích và tối ưu bố cục struct

**Yêu cầu:**
1. Tạo một struct với các thành phần có kiểu dữ liệu khác nhau.
2. In ra kích thước tổng thể và offset của từng thành phần.
3. Sắp xếp lại các thành phần để giảm thiểu padding và tối ưu kích thước struct.
4. So sánh kích thước trước và sau khi tối ưu.

**Template code:**

```cpp
#include <iostream>

// TODO: Tạo struct ban đầu với các kiểu dữ liệu khác nhau
struct IneffectiveStruct {
    // Thứ tự cần tối ưu
};

// TODO: Tạo struct tối ưu
struct OptimizedStruct {
    // Sắp xếp lại thứ tự để giảm padding
};

void analyzeStruct() {
    IneffectiveStruct ineffective;
    OptimizedStruct optimized;
    
    // TODO: In ra và phân tích kích thước và offset của các thành phần
    
    // TODO: So sánh tổng kích thước
}

int main() {
    analyzeStruct();
    return 0;
}
```

## Bài 5: Tìm và sửa các lỗi liên quan đến bộ nhớ

**Yêu cầu:**
1. Đọc và phân tích đoạn code có chứa các lỗi liên quan đến bộ nhớ.
2. Tìm và sửa các lỗi như memory leak, use-after-free, buffer overflow...
3. Giải thích tại sao đoạn code ban đầu có vấn đề và cách sửa.

**Template code:**

```cpp
#include <iostream>
#include <cstring>

// Code có chứa nhiều lỗi liên quan đến bộ nhớ
void buggyFunction() {
    // Bug 1: Memory leak
    int* numbers = new int[10];
    for (int i = 0; i < 10; i++) {
        numbers[i] = i;
    }
    
    // Bug 2: Buffer overflow
    char name[5];
    strcpy(name, "John Smith");
    std::cout << "Name: " << name << std::endl;
    
    // Bug 3: Dangling pointer
    int* data = new int(42);
    int* ref = data;
    delete data;
    std::cout << "Value: " << *ref << std::endl;
    
    // Bug 4: Double free
    int* value = new int(100);
    delete value;
    delete value;
}

// TODO: Viết hàm sửa lỗi
void fixedFunction() {
    // TODO: Sửa các lỗi từ buggyFunction
}

int main() {
    // Chạy phiên bản có lỗi
    std::cout << "Running buggy function:" << std::endl;
    buggyFunction();  // Có thể gây crash
    
    std::cout << "\nRunning fixed function:" << std::endl;
    fixedFunction();
    
    return 0;
}
```
