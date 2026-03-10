#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//đọc dữ liệu từ file và ghi vào vector
struct Song {
    int duration;
    std::string title;
    std::string path;
};

// Hàm phân tích Playlist (Yêu cầu bài tập)
std::vector<Song> loadPlaylist(const char* filepath) {
    std::vector<Song> playlist;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Loi: Khong the mo file " << filepath << std::endl;
        return playlist;
    }

    std::string line;
    int currentDuration = 0;
    std::string currentTitle = "";

    while (std::getline(file, line)) {
        // 1. Bỏ qua dòng trống
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;

        // 2. Kiểm tra nếu là dòng Metadata (#EXTINF)
        if (line.find("#EXTINF:") == 0) {
            size_t colonPos = line.find(':');
            size_t commaPos = line.find(',');

            if (colonPos != std::string::npos && commaPos != std::string::npos) {
                try {
                    std::string durStr = line.substr(colonPos + 1, commaPos - colonPos - 1);
                    currentDuration = std::stoi(durStr); // Trích xuất thời lượng
                    currentTitle = line.substr(commaPos + 1); // Trích xuất tên bài hát
                } catch (...) {
                    // Nếu lỗi định dạng số, bỏ qua metadata này
                    currentDuration = 0;
                    currentTitle = "Unknown Title";
                }
            }
            continue; 
        }

        // 3. Bỏ qua các dòng comment khác bắt đầu bằng #
        if (line[0] == '#') continue;

        // 4. Nếu không có #, dòng này là đường dẫn file
        Song s;
        s.duration = currentDuration;
        s.title = currentTitle.empty() ? "No Title" : currentTitle;
        s.path = line;
        
        playlist.push_back(s);

        // Reset lại để đợi bài tiếp theo
        currentDuration = 0;
        currentTitle = "";
    }

    file.close();
    return playlist;
}

int main() {
    const char* filename = "my_playlist.m3u";

    // --- BƯỚC 1: TẠO FILE TEST MẪU ---
    std::ofstream out(filename);
    out << "#EXTM3U\n"; // Header file m3u
    out << "# Day la comment, se bi bo qua\n";
    out << "\n"; // Dong trong, se bi bo qua
    out << "#EXTINF:180,Ed Sheeran - Shape of You\n";
    out << "/music/pop/shape_of_you.mp3\n";
    out << "#EXTINF:245,Queen - Bohemian Rhapsody\n";
    out << "C:\\Users\\Music\\rock\\bohemian_rhapsody.flac\n";
    out << "/music/unknown_song.mp3\n"; // Bai nay khong co metadata dung truoc
    out.close();

    // --- BƯỚC 2: CHẠY HÀM LOAD PLAYLIST ---
    std::vector<Song> myPlaylist = loadPlaylist(filename);

    // --- BƯỚC 3: IN KẾT QUẢ ĐỂ KIỂM TRA ---
    std::cout << "--- KET QUA PHAN TICH PLAYLIST ---" << std::endl;
    std::cout << "Tim thay " << myPlaylist.size() << " bai hat.\n" << std::endl;

    for (size_t i = 0; i < myPlaylist.size(); ++i) {
        std::cout << "Bai " << i + 1 << ":" << std::endl;
        std::cout << "  - Title   : " << myPlaylist[i].title << std::endl;
        std::cout << "  - Duration: " << myPlaylist[i].duration << " giay" << std::endl;
        std::cout << "  - Path    : " << myPlaylist[i].path << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    return 0;
}