#include "AddAlbumToQueue.h"

void addAlbumToQueue(const std::string& albumName,
                     const MusicLibrary& library,
                     PlaybackQueue& queue)
{
    for(const auto& song : library.getSongs()){
        if(song.album == albumName){
            queue.addSong(song);
        }
    }
}