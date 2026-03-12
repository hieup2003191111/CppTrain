#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <windows.h> 

using namespace std;
class MediaItem {
public:
    virtual void play() const { 
        cout<<"* ... phát chung ... */ "<<endl;
    }
};

class Song : public MediaItem {
public:
    std::string artist;
    void play() const override {   
        cout<<"* ... phát với lời ... */ "<<endl;
 }
};

int main() {
    SetConsoleOutputCP(65001); // Hiển thị tiếng Việt
    vector<unique_ptr<MediaItem>> playlist; // VẤN ĐỀ NẰM Ở ĐÂY
    unique_ptr<Song> s = make_unique<Song>();
    s->artist = "Queen";

    playlist.push_back(move(s)); 

    // playlist[0] giờ là một MediaItem, không còn là Song.
    // Thông tin 'artist' bị mất.
    // Lời gọi này sẽ thực thi MediaItem::play(), không phải Song::play()
    playlist[0]->play();

    return 0;
}