#include <iostream>
#include <string>

struct Song {
    std::string title;
    Song* next;
};

// HÀM BỊ LỖI: Truyền tham trị (Pass by Value)
// 'current' ở đây chỉ là một bản sao của con trỏ truyền vào
void selectNextInPlaylist_WRONG(Song*& current) {
    std::cout << "\n[Trong ham] Dia chi ban dau cua 'current': " << current << std::endl;
    
    if (current != nullptr && current->next != nullptr) {
        current = current->next; // Chuyển sang bài tiếp theo
        std::cout << "[Trong ham] 'current' da duoc cap nhat thanh: " << current << " (" << current->title << ")" << std::endl;
    }
    
    std::cout << "[Trong ham] Chuan bi thoat ham..." << std::endl;
}

int main() {
    // 1. Tao danh sach lien ket: Song A -> Song B
    Song songB = {"Song B", nullptr};
    Song songA = {"Song A", &songB};

    // 2. Con tro dang nghe (nowPlaying) tro vao Song A
    Song* nowPlaying = &songA;

    std::cout << "--- TRUOC KHI GOI HAM ---" << std::endl;
    std::cout << "nowPlaying dang tro den: " << nowPlaying << " (" << nowPlaying->title << ")" << std::endl;

    // 3. Goi ham de chuyen sang bai tiep theo
    selectNextInPlaylist_WRONG(nowPlaying);

    std::cout << "\n--- SAU KHI GOI HAM ---" << std::endl;
    std::cout << "nowPlaying dang tro den: " << nowPlaying << " (" << nowPlaying->title << ")" << std::endl;

    if (nowPlaying == &songA) {
        std::cout << "\n=> KET QUA: nowPlaying VAN DUNG YEN O SONG A! Ham khong co tac dung." << std::endl;
    }

    return 0;
}//phân biêt khi truyền ** ,*&,* vào hàm(dùng trong linked list quản lí con trỏ)
// **,*& có thể thay đổi con trỏ gốc
// * chỉ thay đổi con trỏ khi ở trong hàm,ngoài hàm sẽ về như ban đầu