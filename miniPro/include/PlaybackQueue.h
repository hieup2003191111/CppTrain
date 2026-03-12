#ifndef PLAYBACKQUEUE_H
#define PLAYBACKQUEUE_H

#include <list>
#include "Song.h"

class PlaybackQueue {
private:
    std::list<Song> songs;
    std::list<Song>::iterator current;

public:
    PlaybackQueue();

    void addSong(const Song& song);

    void removeSong(int songID);

    Song* getCurrentSong();

    void playNext();
};

#endif