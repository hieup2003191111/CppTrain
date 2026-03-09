#include <iostream>

// Kỹ thuật 1: Dùng Anonymous Namespace để ẩn hàm nội bộ
namespace {
    bool internal_recursive_parse() {
        std::cout << "[Internal] Dang chay thuat toan de quy phuc tap..." << std::endl;
        return true;
    }
}

// Kỹ thuật 2 (Dòng này để bạn test thử nếu không dùng namespace):
// __attribute__((visibility("hidden"))) void hidden_helper() {}

void activate_parser() {
    std::cout << "[Public] Bat dau kich hoat Parser..." << std::endl;
    internal_recursive_parse(); // Goi ham noi bo hop le
}