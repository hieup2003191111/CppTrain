#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
using namespace std;  
struct Song {
    int id;
    string title;
};
vector<Song> playlist = {
    {101, "Bohemian Rhapsody"},
    {102, "Hotel California"},
    {103, "Imagine"}
};
Song* findSong(int idSong){
    for(auto &song : playlist){
        if(song.id==idSong) return &song;
    }
    return nullptr;
}
Song* findSong(string titleSong){
    for(auto &song : playlist){
        if(song.title==titleSong) return &song;
    }
    return nullptr;
}
int main(){
    SetConsoleOutputCP(65001);
    Song* result1=findSong(101);
    if(result1==nullptr) {
        cout<<"không tìm thấy"<<endl;
    }
    else cout<<"bài hát cần tìm là  "<<result1->title<<endl;
    Song* result2=findSong("Imagine");
    if(result2==nullptr) {
        cout<<"không tìm thấy"<<endl;
    }
    else cout<<"bài hát cần tìm là  "<<result1->id<<endl;
}
//giải thích
//khi dùng overload,hàm sẽ dựa vào kiểu dữ liệu của tham số để chọn ra logic đÚng