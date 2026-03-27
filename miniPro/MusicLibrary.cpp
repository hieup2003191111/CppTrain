#include <iostream>
#include "MusicLibrary.h"

using namespace std;

void MusicLibrary::addSong(const Song& s) {
    songs.push_back(s);
}
void MusicLibrary::buildAllIndices() {
    songIndexByID.clear();
    songIndexByTitle.clear();
    artistIndex.clear();

    for (size_t i = 0; i < songs.size(); ++i) {
        Song* sPtr = &songs[i];
        songIndexByID[sPtr->id] = sPtr;
        songIndexByTitle[sPtr->title] = sPtr;
        artistIndex[sPtr->artist].push_back(sPtr);
    }
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

Song* MusicLibrary::findSongByID(int id){
    auto it = songIndexByID.find(id);
    if(it!=songIndexByID.end()){
        return it->second;
    }
    return nullptr;
}
Song* MusicLibrary::findSongByTitle(const string& title){
    auto it = songIndexByTitle.find(title);
    if(it!=songIndexByTitle.end()){
        return it->second;
    }
    return nullptr;    
}

void MusicLibrary::buildArtistIndex() {
    artistIndex.clear(); 
    
    for (size_t i = 0; i < songs.size(); ++i) {
        // Lấy tên nghệ sĩ của bài hát thứ i
        std::string artist = songs[i].artist;
        // Lấy địa chỉ của bài hát đó và đẩy vào vector của nghệ sĩ tương ứng
        artistIndex[artist].push_back(&songs[i]);
    }
}
    vector<Song*> MusicLibrary::findByArtist(const string& artist){
        auto it = artistIndex.find(artist);
        if(it!=artistIndex.end()){
            return it->second;
        }
        return vector<Song*>();
    }

