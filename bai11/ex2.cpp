#include <iostream>  
#include <vector>  
#include <string>  
#include <windows.h> 
#include <list>
using namespace std;
//hàm static có thể gọi mà không cầN khởi tạo đối tượng,nhưng chỉ có thể tiếp cận được những biến static
class Song{
private:
    const int songId;
    static int totalSongCreated;
    string title;
public:
    Song(int id,string title) : songId(id),title(title){
        totalSongCreated++;
    }
    static int getTotalSongs() {
        return totalSongCreated;
    }
    void display() const {
        std::cout << "ID: " << songId << " | Title: " << title << std::endl;
    }
};
int Song::totalSongCreated = 0;
int main() {
    Song s1(101, "Shape of You");
    Song s2(102, "Bohemian Rhapsody");

    s1.display();
    s2.display();
    
    // Gọi hàm static thông qua tên lớp
    std::cout << "Tong so bai hat trong he thong: " << Song::getTotalSongs() << std::endl;

    return 0;
}