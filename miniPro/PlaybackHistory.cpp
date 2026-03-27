#include "PlaybackHistory.h"
#include <stdexcept>
void PlaybackHistory::addSong(const Song& s){
    HistoryStack.push(s);
}
Song PlaybackHistory::playPreviousSong(){
    if(!HistoryStack.empty()){
        Song lastSong = HistoryStack.top();
        HistoryStack.pop();
        return lastSong;
    }
throw runtime_error("Lich su trong!");
}
