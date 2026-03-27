#ifndef PLAYBACKHISTORY_H
#define PLAYBACKHISTORY_H
#include "Song.h"
#include <stack>
using namespace std;
class PlaybackHistory{
private:
stack<Song> HistoryStack;
public:
void addSong(const Song& s);
Song playPreviousSong();
};
#endif