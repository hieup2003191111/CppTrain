#include <iostream>
using namespace std;

// CÁCH 1: Con trỏ trỏ đến mảng (Pointer to Array)
// presets là con trỏ trỏ đến một mảng có 10 phần tử float.
void loadPreset_Method1(float (*presets)[10], int rows) {
    cout << "--- Method 1: Pointer to Array ---" << endl;
    cout << "Total size in bytes: " << sizeof(presets) << endl; // Sẽ in ra 5*10*4 = 200 bytes
    // Truy cập hàng 0, cột 5
    cout << "Value at [0][5]: " << presets[0][5] << endl;
}

// CÁCH 2: Tham chiếu đến mảng (Reference to Array)
// presets là tên gọi khác của chính mảng gốc [5][10].
void loadPreset_Method2(float (&presets)[5][10]) {
    cout << "--- Method 2: Reference to Array ---" << endl;
    // Tính tổng kích thước để minh chứng tính an toàn
    cout << "Total size in bytes: " << sizeof(presets) << endl; // Sẽ in ra 5*10*4 = 200 bytes
}

int main() {
    // Khai báo mảng 2D gồm 5 hàng, 10 cột
    float user_presets[5][10] = {0};
    user_presets[0][5] = 12.5f; // Gán thử một giá trị

    // Gọi Cách 1: Phải truyền thêm số hàng vì hàm chỉ biết số cột là 10
    loadPreset_Method1(user_presets, 5);

    // Gọi Cách 2: Không cần truyền số hàng, vì nó đã nằm trong kiểu dữ liệu (&)[5][10]
    loadPreset_Method2(user_presets);

    return 0;
}