#include <iostream>  
#include <vector>  
#include <string>  
#include <windows.h> 
#include <list>
using namespace std;
struct Song {
    string title;
    int id;
};
class Playlist{
private:
    Song* song_list;
    int capacity;
public:
    Playlist(int size){
        capacity = size;
        song_list = new Song[capacity];  
    }
    ~Playlist(){}
};

int main(){
    
    return 0;

}