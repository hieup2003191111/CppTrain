#include <iostream>
#include <vector>
#include <stack> // Bước 1: Thêm thư viện ngăn xếp

struct Playlist {
    std::vector<Playlist> nestedPlaylists;
    std::string name; // Giả sử có tên để dễ theo dõi
};

void parsePlaylist(Playlist root) {
    // Bước 2: Tạo một cái "túi" chứa các Playlist cần xử lý
    // std::stack này sẽ tự động cấp phát bộ nhớ trên HEAP
    std::stack<Playlist> s;

    // Bước 3: Bỏ Playlist gốc vào túi
    s.push(root);

    // Bước 4: Chừng nào trong túi còn đồ thì còn làm
    while (!s.empty()) {
        // Lấy Playlist trên cùng ra để xử lý
        Playlist current = s.top();
        s.pop();

        // Giả sử in tên Playlist đang xử lý
        std::cout << "Processing: " << current.name << std::endl;

        // Bước 5: Tìm xem trong Playlist này có "con" không?
        // Nếu có, bỏ hết các con vào túi để tí nữa xử lý tiếp
        for (const auto& nested : current.nestedPlaylists) {
            s.push(nested);
        }
    }
}