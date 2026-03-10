#include <iostream>  
#include <vector>  
#include <string>  
#include <windows.h> 
#include <list>

struct Song { std::string title; };  
int main() {  
 SetConsoleOutputCP(65001);
 std::vector<Song> playlist = {{"Song A"}, {"Song B"}};  
 int currentIndex = 0;  
  
 // 1. Get a pointer to the current song  
 Song* currentSongPtr = &playlist[currentIndex];  
 std::cout << "Before reallocation: " << currentSongPtr->title << std::endl;    
 std::cout <<"địa chỉ cũ là "<<currentSongPtr<<std::endl;
 // 2. Add many new songs, causing the vector to reallocate memory   playlist.push_back({"Song C"});  
 playlist.push_back({"Song D"});  
 playlist.push_back({"Song E"});  
  std::cout <<"địa chỉ mới là "<<&playlist[currentIndex]<<std::endl;
 // 3. PROBLEM: The 'currentSongPtr' may now be invalid  
  std::cout << "After reallocation: " << (&playlist[currentIndex])->title << std::endl;  // CRASH or prints garbage data!  
  
// Giải pháp 2: Dùng std::list
// std::list<Song> playlist = {{"Song A"}, {"Song B"}};
// Song* currentSongPtr = &playlist.front(); // Lấy địa chỉ bài đầu tiên

// playlist.push_back({"Song C"}); // Thêm phần tử không làm di dời bài cũ

// // currentSongPtr vẫn trỏ đúng địa chỉ cũ của Song A
// std::cout << "Still safe: " << currentSongPtr->title << std::endl;

 return 0;  
}  
//so sánh list và vector
//vector:
//-có thể truy cập phần thử thông qua index
//-khi thêm,xoá đầu cuối sẽ dịch phần tử làm mất địa chỉ
//list:
//-không truy cập qua index được,buộc phải duyệt từ đầu
//-có thể thêm bớt vị trí tuỳ ý đơn giản
