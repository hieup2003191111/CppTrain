#include <iostream>
#include <stdint.h>

struct Config {
    int sampleRate;
    int channels;
};

int main() {
    // Giả lập các vùng nhớ
    uint32_t hardware_addr = 0x400F0010;
    float buffer_a = 0.1f, buffer_b = 0.2f;
    Config global_cfg = {44100, 2};
    Config spare_cfg = {48000, 1};

    // --- 1. Pointer to Constant Data (Con trỏ trỏ đến dữ liệu hằng) ---
    // Đọc từ phải sang: dac_register_ptr là con trỏ (*) trỏ đến uint32_t hằng (const)
    const uint32_t* dac_register_ptr = &hardware_addr;

    // *dac_register_ptr = 0; // LỖI: Không cho phép sửa giá trị tại thanh ghi
    dac_register_ptr = nullptr; // OK: Có thể trỏ đi nơi khác


    // --- 2. Constant Pointer to Data (Con trỏ hằng trỏ đến dữ liệu) ---
    // Đọc từ phải sang: active_audio_buffer là hằng số (const) con trỏ (*) trỏ đến float
    float* const active_audio_buffer = &buffer_a;

    *active_audio_buffer = 0.5f; // OK: Có thể sửa dữ liệu trong bộ đệm
    // active_audio_buffer = &buffer_b; // LỖI: Không cho phép trỏ sang bộ đệm khác


    // --- 3. Constant Pointer to Constant Data (Con trỏ hằng trỏ đến dữ liệu hằng) ---
    // Đọc từ phải sang: rom_config là hằng số (const) con trỏ (*) trỏ đến Config hằng (const)
    const Config* const rom_config = &global_cfg;

    // rom_config->sampleRate = 96000; // LỖI: Không cho phép sửa dữ liệu cấu hình
    // rom_config = &spare_cfg;        // LỖI: Không cho phép trỏ sang vùng cấu hình khác

    std::cout << "Khai bao thanh cong va bao ve du lieu dung quy tac!" << std::endl;

    return 0;
}
//Để hiểu const bảo vệ cái gì, hãy đọc khai báo từ phải sang trái: