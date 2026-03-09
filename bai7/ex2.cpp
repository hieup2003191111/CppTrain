#include <iostream>  
#include <string>
using namespace std;
struct Song {
    string title;
};
Song listSong[3] = {{"A"},{"B"},{"C"}};

Song* findByTitle(const string& title){
    for(int i=0;i<3;i++){
        if(listSong[i].title==title){
            return &listSong[i];
        }
    }
    return nullptr;
}
int main(){
    Song* found = findByTitle("hieu");
    if(found!=nullptr){
        cout<<"day la bai hat cua "<<found->title<<endl;
    }
    else{
        cout<<"khong tim thay"<<endl;
    }
    return 0;
}