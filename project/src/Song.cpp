#include "Song.h"
Song::Song(const int id,const std::string& title,const std::string& artist,const std::string& album,int duration)
:id(id),title(title),artist(artist),album(album),duration(duration){
}
int Song::getId() const{
    return id;
}
std::string Song::getTilte() const{
    return title;
}
std::string Song::getArtist() const{
    return artist;
}
int Song::getDuration(){
    return duration;
}
void Song::display(){
    int* const p;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Artist: " << artist << std::endl;
        std::cout << "Album: " << album << std::endl;
        std::cout << "Duration: " << duration << " seconds" << std::endl;   
}