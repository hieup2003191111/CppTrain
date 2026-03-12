#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <vector>
#include <string>
#include "Song.h"

class MusicLibrary {
private:
    std::vector<Song> songs;

public:
    void addSong(const Song& s);

    void removeSong(int id);

    Song* getSong(int id);

    void getAll();

    const vector<Song> & getSongs () const ;
};

#endif