#include "ShuffleManager.h"
using namespace std;

ShuffleManager::ShuffleManager():currentIndex(0){}
void ShuffleManager::initSuffle(const vector<Song>& songs){
    songsTemp = songs;
    // Sử dụng bộ sinh số ngẫu nhiên hiện đại của C++11
    std::random_device rd;
    std::mt19937 g(rd());
    
    // Xáo trộn vector
    shuffle(songsTemp.begin(), songsTemp.end(), g);
    playedID.clear();
    currentIndex = 0;
}
Song ShuffleManager:: nextSong(){
    if(songsTemp.empty()){
        return Song(0,"none","none","none",0);
    }
    if(playedID.size()>=songsTemp.size()){
        cout<<"end cycle,reset now"<<endl;
        resetCycle();
    }
    while(currentIndex<songsTemp.size()){
        Song s=songsTemp[currentIndex];
        if(playedID.find(s.id)==playedID.end()){
            playedID.insert(s.id);
            currentIndex++;
            return s;
        }
        currentIndex++;
        
    }
    return nextSong();
}
void ShuffleManager::resetCycle() {
    playedID.clear();
    currentIndex = 0;
    random_device rd;
    mt19937 g(rd());
    shuffle(songsTemp.begin(), songsTemp.end(), g);
}

bool ShuffleManager::isCycleEnd() const {
    return playedID.size() == songsTemp.size();
}