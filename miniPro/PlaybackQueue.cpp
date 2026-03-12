#include <iostream>
#include "PlaybackQueue.h"

using namespace std;

PlaybackQueue::PlaybackQueue() {
    current = songs.end();
}

void PlaybackQueue::addSong(const Song& song){
    songs.push_back(song);
    if(current == songs.end())
        current = songs.begin();
}

void PlaybackQueue::removeSong(int songID){
    for(auto s = songs.begin(); s != songs.end(); s++){
        if(s->id == songID){

            if(current == s){
                if(next(current) != songs.end())
                    current = next(s);
                else
                    current = songs.begin();
            }

            songs.erase(s);
            return;
        }
    }
}

Song* PlaybackQueue::getCurrentSong(){
    if(current != songs.end())
        return &(*current);

    return nullptr;
}

void PlaybackQueue::playNext(){
    if(current != songs.end() && next(current) != songs.end())
        current = next(current);
    else
        cout << "end list song" << endl;
}