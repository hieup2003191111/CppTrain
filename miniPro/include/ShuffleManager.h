#ifndef SHUFFLEMANAGER_H
#define SHUFFLEMANAGER_H
#include<iostream>
#include <vector>
#include <random>
#include <set>
#include "Song.h"
#include <algorithm>
class ShuffleManager{
private:
vector<Song> songsTemp;
set<int> playedID;
size_t currentIndex;
public:
ShuffleManager();
void initSuffle(const vector<Song>& s);
Song nextSong();
bool isCycleEnd () const;
void resetCycle();
};
#endif