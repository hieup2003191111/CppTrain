#include <iostream>
#include "Song.h"
#include "MusicLibrary.h"
#include "PlaybackQueue.h"
#include "AddAlbumToQueue.h"

using namespace std;

int main() {

    MusicLibrary library;
    PlaybackQueue queue;

    cout << "===== ADD SONGS TO LIBRARY =====\n";

    library.addSong(Song(1, "Shape of You", "Ed Sheeran", "Divide", 233));
    library.addSong(Song(2, "Perfect", "Ed Sheeran", "Divide", 263));
    library.addSong(Song(3, "Blinding Lights", "The Weeknd", "After Hours", 200));
    library.addSong(Song(4, "Save Your Tears", "The Weeknd", "After Hours", 215));
    library.addSong(Song(5, "Believer", "Imagine Dragons", "Evolve", 204));

    cout << "\n===== LIBRARY =====\n";
    library.getAll();


    // ================================
    // Thêm thủ công vào queue
    // ================================

    cout << "\n===== ADD SONG MANUALLY TO QUEUE =====\n";

    for(const auto &s:library.getSongs()){
        queue.addSong(s);
    }

    Song* current = queue.getCurrentSong();

    if(current){
        cout << "Current song: "
             << current->title
             << " - "
             << current->artist
             << endl;
    }


    // ================================
    // Thêm cả album vào queue
    // ================================

    cout << "\n===== ADD ALBUM 'Divide' TO QUEUE =====\n";

    addAlbumToQueue("Divide", library, queue);


    cout << "\n===== PLAY CURRENT SONG =====\n";

    current = queue.getCurrentSong();

    if(current){
        cout << "Current song: "
             << current->title
             << " - "
             << current->artist
             << endl;
    }


    cout << "\n===== PLAY NEXT =====\n";

    queue.playNext();

    current = queue.getCurrentSong();

    if(current){
        cout << "Current song: "
             << current->title
             << " - "
             << current->artist
             << endl;
    }
    cout << "\n===== PLAY NEXT =====\n";

    queue.playNext();

    current = queue.getCurrentSong();

    if(current){
        cout << "Current song: "
             << current->title
             << " - "
             << current->artist
             << endl;
    }


    cout << "\n===== REMOVE CURRENT SONG =====\n";

    if(current){
        queue.removeSong(current->id);
    }

    current = queue.getCurrentSong();

    if(current){
        cout << "Current song: "
             << current->title
             << " - "
             << current->artist
             << endl;
    }
    else{
        cout << "No current song\n";
    }


    cout << "\n===== PLAY NEXT AGAIN =====\n";

    queue.playNext();

    current = queue.getCurrentSong();

    if(current){
        cout << "Current song: "
             << current->title
             << " - "
             << current->artist
             << endl;
    }
    else{
        cout << "End of queue\n";
    }
    
    cout << "\n===== PLAY NEXT AGAIN =====\n";

    queue.playNext();

    current = queue.getCurrentSong();

    if(current){
        cout << "Current song: "
             << current->title
             << " - "
             << current->artist
             << endl;
    }
    else{
        cout << "End of queue\n";
    }


    return 0;
}