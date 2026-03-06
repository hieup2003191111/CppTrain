#include <iostream>
#include <vector>
#include <windows.h> // Thêm thư viện này
using namespace std;  
#include <stack> // Bước 1: Thêm thư viện ngăn xếp
struct Playlist{
    vector<Playlist> nestedPlaylist;
    string name;
};
void loadPlaylist(Playlist list){
    std::stack<Playlist> s;
    s.push(list);
    //lặp đến node con cuối
    while(!s.empty()){
        Playlist current = s.top();//in ra Playlist đang xét
        s.pop();
        cout<<"Playlist đang chạy là "<<current.name<<endl;
        //push các node con của Playlist hiện tại vào stack
        for(auto &nest : current.nestedPlaylist){
            s.push(nest);
        }
    }
}
int main(){
    SetConsoleOutputCP(65001);
    Playlist p4 = {{},"4"};
    Playlist p5 = {{},"5"};
    Playlist p6 = {{},"6"};
    Playlist p7 = {{},"7"};
    Playlist p2 = {{p4,p5},"2"};
    Playlist p3 = {{p6,p7},"3"};
    Playlist p1 = {{p2,p3},"1"};
    loadPlaylist(p1);
}