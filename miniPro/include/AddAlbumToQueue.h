 #ifndef ADDALBUMTOQUEUE_H
 #define ADDALBUMTOQUEUE_H
 #include "MusicLibrary.h"
 #include "PlaybackQueue.h"
 #include "Song.h"
 #include<string>
 void addAlbumToQueue(const std::string& albumName, const  MusicLibrary& library, PlaybackQueue& queue);
 #endif