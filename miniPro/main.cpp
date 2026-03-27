#include <iostream>
#include "Song.h"
#include "MusicLibrary.h"
#include "PlaybackQueue.h"
#include "AddAlbumToQueue.h"
#include "PlaybackHistory.h"
#include "ShuffleManager.h"

using namespace std;

int main() {

    MusicLibrary library;
    PlaybackQueue queue;
    PlaybackHistory history;
    ShuffleManager sm;

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
    library.buildAllIndices();
    cout<<"tim kiem theo id"<<endl;
    Song* result = library.findSongByID(3);
    cout<< "ID: " << result->id
             << " | Title: " << result->title
             << " | Artist: " << result->artist
             << " | Album: " << result->album
             << " | Duration: " << result->duration << "s" << endl;
    cout<<"tim kiem theo artist"<<endl;
    vector<Song*> results = library.findByArtist("The Weeknd");
    for(Song* s :  results){
    cout<< "ID: " << s->id
             << " | Title: " << s->title
             << " | Artist: " << s->artist
             << " | Album: " << s->album
             << " | Duration: " << s->duration << "s" << endl;

    }
    history.addSong(Song(1, "Shape of You", "Ed Sheeran", "Divide", 233));
    history.addSong(Song(2, "Perfect", "Ed Sheeran", "Divide", 263));
    history.addSong(Song(3, "Blinding Lights", "The Weeknd", "After Hours", 200));
    history.addSong(Song(4, "Save Your Tears", "The Weeknd", "After Hours", 215));
    history.addSong(Song(5, "Believer", "Imagine Dragons", "Evolve", 204));
    Song pre1 = history.playPreviousSong();
    cout << "Back 1: " << pre1.title << endl;

    // Lấy tiếp bài trước đó nữa (Bài ID 4)
    Song pre2 = history.playPreviousSong();
    cout << "Back 2: " << pre2.title << endl;
    cout << "\n===== TESTING SMART SHUFFLE (3 CYCLES) =====\n";
    
    // Nạp 5 bài hát từ thư viện vào ShuffleManager
    sm.initSuffle(library.getSongs()); 

    // Chạy 12 lần để quan sát sự thay đổi giữa các chu kỳ (mỗi chu kỳ 5 bài)
    for (int i = 1; i <= 16; i++) {
        Song s = sm.nextSong();
        
        cout << "Shuffle Play #" << i << ": [ID " << s.id << "] " << s.title << endl;

        // In dấu gạch ngang khi kết thúc một chu kỳ để dễ quan sát
        if (i % 5 == 0) {
            cout << "------------------------------------------- (End of Cycle)" << endl;
        }
    }
    return 0;
}