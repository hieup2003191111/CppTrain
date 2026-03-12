#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// 1. Lớp cơ sở trừu tượng (Abstract Base Class)
class MediaItem {
public:
    // Hàm ảo thuần túy: bắt buộc các lớp con phải tự định nghĩa nội dung
    virtual std::string getDisplayText() = 0; 

    // Destructor ảo: cực kỳ quan trọng để tránh leak bộ nhớ 
    virtual ~MediaItem() {} 
};

// 2. Lớp Song (Bài hát)
class Song : public MediaItem {
private:
    std::string artist;
    std::string title;
public:
    Song(std::string a, std::string t) : artist(a), title(t) {}

    // Ghi đè hàm hiển thị theo định dạng riêng của bài hát
    std::string getDisplayText() override {
        return artist + " - " + title;
    }
};

// 3. Lớp Podcast
class Podcast : public MediaItem {
private:
    std::string showName;
    std::string episodeTitle;
public:
    Podcast(std::string s, std::string e) : showName(s), episodeTitle(e) {}

    // Ghi đè hàm hiển thị theo định dạng riêng của Podcast
    std::string getDisplayText() override {
        return showName + ": " + episodeTitle;
    }
};
int main() {
    // // THỬ NGHIỆM LỖI:
    //  std::vector<MediaItem> playlist; 
    //  // Tạo một đối tượng Song thực thụ
    // Song mySong("Queen", "Bohemian Rhapsody");

    // // Thử thêm đối tượng này vào vector kiểu MediaItem
    // playlist.push_back(mySong);
    //c1:dùng con trỏ thô MediaItem*,sau đó delete bằng vòng lặp
    //c2:dùng unique_ptr
    vector<unique_ptr<MediaItem>> playlist;
    playlist.push_back(make_unique<Song>("A","B"));
    cout<<playlist.back()->getDisplayText();
    for (const auto& item : playlist) {
        // Gọi hàm ảo getDisplayText()
        cout << ">> " << item->getDisplayText() << endl;
    }
    
    return 0;
}