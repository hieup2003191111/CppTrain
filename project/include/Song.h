#ifndef SONG_H
#define SONG_H
#include<iostream>
class Song{
private:
    int id;
    std::string title,artist,album;
    int duration;
public:
//constructor
Song(const int id,const std::string& title,const std::string& artist,const std::string& album,int duration);
int getId() const;
std::string getTilte() const;
std::string getArtist() const;
std::string getAlbum() const;
int getDuration();
void display();

};
#endif