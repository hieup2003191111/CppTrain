#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <vector>
#include <string>
#include "Song.h"
#include <unordered_map>
#include <map>
using namespace std;
class MusicLibrary {
private:
    std::vector<Song> songs;
    unordered_map<int,Song*> songIndexByID;
    map<std::string, Song*> songIndexByTitle;
    unordered_map<std::string,vector<Song*>> artistIndex;
public:
    void buildArtistIndex();

    void buildAllIndices();

    vector<Song*> findByArtist(const string& artist);

    Song* findSongByID(int id);

    Song* findSongByTitle(const std::string& title);

    void addSong(const Song& s);

    void removeSong(int id);

    Song* getSong(int id);

    void getAll();

    const vector<Song> & getSongs () const ;
};

#endif