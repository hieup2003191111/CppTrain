#include <iostream>
#include <string>
#include "Playlist.h"

// Định nghĩa các struct đơn giản theo yêu cầu 3
struct Song {
    std::string title;
    std::string artist;
};

struct PodcastEpisode {
    std::string title;
    int episodeNumber;
};

int main() {
    // 1. Tạo Playlist cho Bài hát
    Playlist<Song> musicPlaylist;
    musicPlaylist.addItem({"Loi Nho", "Den Vau"});
    musicPlaylist.addItem({"See Tinh", "Hoang Thuy Linh"});

    std::cout << "--- Music Playlist ---\n";
    std::cout << "Current: " << musicPlaylist.getCurrentItem().title << " by " << musicPlaylist.getCurrentItem().artist << "\n";
    
    if (musicPlaylist.hasNext()) {
        musicPlaylist.next();
        std::cout << "Next: " << musicPlaylist.getCurrentItem().title << "\n";
    }

    // 2. Tạo Playlist cho Podcast
    Playlist<PodcastEpisode> podcastPlaylist;
    podcastPlaylist.addItem({"Hoc ve Template", 101});
    podcastPlaylist.addItem({"Tam ly hoc toi pham", 42});

    std::cout << "\n--- Podcast Playlist ---\n";
    std::cout << "Current Episode: " << podcastPlaylist.getCurrentItem().title 
              << " (#" << podcastPlaylist.getCurrentItem().episodeNumber << ")\n";

    return 0;
}