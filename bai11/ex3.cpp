#include <iostream>
#include <cstring>

class AlbumArt {
private:
    char* image_buffer;
    size_t buffer_size;

public:
    // Constructor: Cấp phát bộ nhớ trên Heap
    AlbumArt(size_t size, const char* dummy_data) : buffer_size(size) {
        image_buffer = new char[buffer_size];
        std::memcpy(image_buffer, dummy_data, buffer_size);
        std::cout << "[Constructor] Da cap phat vung nho tai: " << (void*)image_buffer << std::endl;
    }
    //constructor copy deep
    AlbumArt(const AlbumArt &other ) : buffer_size(other.buffer_size){
        image_buffer = new char[buffer_size];
        std:memcpy(image_buffer,other.image_buffer,buffer_size);
        std::cout << "[Copy Constructor] DEEP COPY tai: " << (void*)image_buffer << std::endl;
    }

    // Destructor: Giai phong bộ nhớ
    ~AlbumArt() {
        std::cout << "[Destructor] Dang giai phong vung nho tai: " << (void*)image_buffer << std::endl;
        delete[] image_buffer; 
    }

    // Ham hien thi thong tin
    void showInfo(const std::string& name) {
        std::cout << "Object [" << name << "] dang tro den: " << (void*)image_buffer << std::endl;
    }
};

// void simulateError() {
//     std::cout << "--- Bat dau ham simulateError ---" << std::endl;
    
//     AlbumArt art1(1024, "Fake Image Data"); // art1 cấp phát vùng nhớ A
    
//     // Day chinh la Shallow Copy! 
//     // Trinh bien dich copy gia tri dia chi tu art1 sang art2
//     AlbumArt art2 = art1; 

//     art1.showInfo("art1");
//     art2.showInfo("art2");

//     std::cout << "--- Ket thuc ham simulateError ---" << std::endl;
// } // <--- LOI XAY RA TAI DAY

void simulateDeepCopy() {
    std::cout << "--- Bat dau ham simulateDeepCopy ---" << std::endl;
    
    AlbumArt art1(1024, "Original Image Data");
    
    // Gọi Deep Copy Constructor
    AlbumArt art2 = art1; //tương đương AlbumArt art2(art1)

    art1.showInfo("art1");
    art2.showInfo("art2");

    std::cout << "--- Ket thuc ham simulateDeepCopy (art2 va art1 se bi huy) ---" << std::endl;
}
int main() {
    // simulateError();
    simulateDeepCopy();
    std::cout << "Chuong trinh ket thuc an toan." << std::endl;
    return 0;
}