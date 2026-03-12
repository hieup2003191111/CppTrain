#include <iostream>
#include <vector>
#include <list>
#include <string>

// =====================================================
// YÊU CẦU 1 & 2: FUNCTION TEMPLATE findItemByID
// =====================================================

/**
 * @brief Hàm tìm kiếm tổng quát dựa trên thuộc tính .id
 * @tparam Container: Kiểu của vật chứa (vector, list, ...)
 * @tparam IDType: Kiểu dữ liệu của ID (int, string, ...)
 * @return iterator trỏ đến phần tử tìm thấy hoặc container.end()
 */
template <typename Container, typename IDType>
typename Container::iterator findItemByID(Container& container, const IDType& id) {
    
    // Sử dụng vòng lặp iterator để có thể duyệt qua cả vector và list
    for (auto it = container.begin(); it != container.end(); ++it) {
        
        // Yêu cầu 2: So sánh thuộc tính .id của phần tử hiện tại với id cần tìm
        // Lưu ý: Phần tử trong container bắt buộc phải có trường tên là 'id'
        if (it->id == id) {
            return it; // Trả về iterator tại vị trí tìm thấy
        }
    }
    
    // Trả về iterator end() nếu duyệt hết danh sách mà không thấy
    return container.end();
}

// =====================================================
// YÊU CẦU 3: ĐỊNH NGHĨA STRUCT VÀ TEST TRONG MAIN
// =====================================================

struct Song {
    int id;               // ID kiểu int
    std::string title;
};

struct Artist {
    std::string id;       // ID kiểu string
    std::string name;
};

int main() {
    // --- Test 1: Tìm kiếm trong std::vector với ID kiểu int ---
    std::vector<Song> playlist = {
        {101, "See Tình"},
        {202, "Lạc Trôi"},
        {303, "Waiting For You"}
    };

    std::cout << "--- Search in Vector<Song> ---\n";
    int searchID = 202;
    auto itSong = findItemByID(playlist, searchID);

    if (itSong != playlist.end()) {
        std::cout << "Found: " << itSong->title << " (ID: " << itSong->id << ")\n";
    } else {
        std::cout << "Song not found.\n";
    }

    // --- Test 2: Tìm kiếm trong std::list với ID kiểu string ---
    // Điều này chứng minh hàm template hoạt động với bất kỳ Container nào hỗ trợ iterator
    std::list<Artist> artists = {
        {"ART_01", "Đen Vâu"},
        {"ART_02", "Sơn Tùng M-TP"}
    };

    std::cout << "\n--- Search in List<Artist> ---\n";
    std::string searchArtID = "ART_01";
    auto itArtist = findItemByID(artists, searchArtID);

    if (itArtist != artists.end()) {
        std::cout << "Found: " << itArtist->name << " (ID: " << itArtist->id << ")\n";
    } else {
        std::cout << "Artist not found.\n";
    }

    return 0;
}