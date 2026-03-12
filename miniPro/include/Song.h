#ifndef SONG_H
#define SONG_H
#include <vector>

using namespace std;

// Struct Song
struct Song {
    int id;
    string title, artist, album;
    int duration;

    Song(int id, const string& title, const string& artist, const string& album, int duration)
        : id(id), title(title), artist(artist), album(album), duration(duration) {}
};
#endif