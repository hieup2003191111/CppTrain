#include <iostream>
#include <cstring>

class Shallow {
public:
    char* data;
    Shallow(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    // Copy constructor (shallow copy)
    Shallow(const Shallow& other) {
        data = other.data; // chỉ copy địa chỉ
    }
    ~Shallow() {
        delete[] data;
    }
};

class Deep {
public:
    char* data;
    Deep(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    // Copy constructor (deep copy)
    Deep(const Deep& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }
    ~Deep() {
        delete[] data;
    }
};

int main() {
    std::cout << "== Shallow Copy ==\n";
    Shallow s1("Hello");
    Shallow s2 = s1; // Shallow copy
    std::cout << "s1: " << s1.data << ", s2: " << s2.data << std::endl;
    strcpy(s2.data, "World");
    std::cout << "After change s2.data:\n";
    std::cout << "s1: " << s1.data << ", s2: " << s2.data << std::endl;
    // Có thể gây lỗi double free khi ra khỏi hàm main

    std::cout << "\n== Deep Copy ==\n";
    Deep d1("Hello");
    Deep d2 = d1; // Deep copy
    std::cout << "d1: " << d1.data << ", d2: " << d2.data << std::endl;
    strcpy(d2.data, "World");
    std::cout << "After change d2.data:\n";
    std::cout << "d1: " << d1.data << ", d2: " << d2.data << std::endl;
    // Không bị lỗi double free, dữ liệu độc lập
    return 0;
}
