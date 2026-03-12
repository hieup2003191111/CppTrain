#include <iostream>
#include "MusicLibrary.h"

using namespace std;

void MusicLibrary::addSong(const Song& s) {
    songs.push_back(s);
}

void MusicLibrary::removeSong(int id) {
    for (auto it = songs.begin(); it != songs.end(); it++) {
        if (it->id == id) {
            songs.erase(it);
            return;
        }
    }
}

Song* MusicLibrary::getSong(int id) {
    for (auto& s : songs) {
        if (s.id == id) return &s;
    }
    return nullptr;
}
const vector<Song>& MusicLibrary::getSongs() const{
    return songs;
}
void MusicLibrary::getAll() {
    for (auto& s : songs) {
        cout << "ID: " << s.id
             << " | Title: " << s.title
             << " | Artist: " << s.artist
             << " | Album: " << s.album
             << " | Duration: " << s.duration << "s" << endl;
    }
}