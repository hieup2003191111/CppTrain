#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Định nghĩa các enum và cấu trúc cần thiết
enum class MediaType {
    Audio,
    Video,
    Image,
    Unknown
};

enum class PlaybackStatus {
    Playing,
    Paused,
    Stopped,
    Error
};

struct MediaInfo {
    std::string title;
    std::string artist;
    std::string album;
    int year;
    int duration; // thời lượng theo giây
    MediaType type;
    
    MediaInfo() : year(0), duration(0), type(MediaType::Unknown) {}
};

// Lớp trừu tượng cho Media Player (Abstraction)
class MediaPlayer {
public:
    // Phương thức thuần ảo
    virtual bool loadMedia(const std::string& path) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void seekTo(int position) = 0;
    virtual PlaybackStatus getStatus() const = 0;
    virtual MediaInfo getMediaInfo() const = 0;
    
    // Destructor ảo
    virtual ~MediaPlayer() {}
    
protected:
    // Thuộc tính chung
    PlaybackStatus status;
    MediaInfo mediaInfo;
    std::string currentFilePath;
    int currentPosition; // vị trí hiện tại (giây)
    
    // Phương thức trợ giúp
    std::string getFileExtension(const std::string& path) const {
        size_t dotPos = path.find_last_of(".");
        if (dotPos != std::string::npos) {
            return path.substr(dotPos + 1);
        }
        return "";
    }
    
    std::string getFileName(const std::string& path) const {
        size_t slashPos = path.find_last_of("/\\");
        if (slashPos != std::string::npos) {
            return path.substr(slashPos + 1);
        }
        return path;
    }
};

// Lớp cụ thể: Audio Player
class AudioPlayer : public MediaPlayer {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    int volume; // 0-100
    bool isMuted;
    std::vector<std::string> supportedFormats;
    
    // Phương thức private
    void extractMetadata(const std::string& path) {
        // Mô phỏng trích xuất metadata từ tệp âm thanh
        mediaInfo.title = getFileName(path);
        mediaInfo.title = mediaInfo.title.substr(0, mediaInfo.title.find_last_of("."));
        
        // Giả lập trích xuất metadata
        if (path.find("song") != std::string::npos) {
            mediaInfo.artist = "Example Artist";
            mediaInfo.album = "Example Album";
            mediaInfo.year = 2023;
            mediaInfo.duration = 180 + rand() % 180; // 3-6 phút
        } else {
            mediaInfo.artist = "Unknown Artist";
            mediaInfo.duration = 60 + rand() % 240; // 1-5 phút
        }
    }
    
    bool isFormatSupported(const std::string& extension) const {
        return std::find(supportedFormats.begin(), supportedFormats.end(), extension) != supportedFormats.end();
    }

public:
    AudioPlayer() : volume(50), isMuted(false) {
        status = PlaybackStatus::Stopped;
        currentPosition = 0;
        
        // Định dạng được hỗ trợ
        supportedFormats = {"mp3", "wav", "aac", "flac", "ogg"};
        
        mediaInfo.type = MediaType::Audio;
    }
    
    bool loadMedia(const std::string& path) override {
        std::string extension = getFileExtension(path);
        
        // Kiểm tra định dạng được hỗ trợ
        if (!isFormatSupported(extension)) {
            std::cout << "Unsupported audio format: " << extension << std::endl;
            return false;
        }
        
        currentFilePath = path;
        currentPosition = 0;
        status = PlaybackStatus::Stopped;
        
        // Trích xuất thông tin tệp
        extractMetadata(path);
        
        std::cout << "Loaded audio: " << mediaInfo.title << std::endl;
        return true;
    }
    
    void play() override {
        if (currentFilePath.empty()) {
            std::cout << "No audio file loaded" << std::endl;
            return;
        }
        
        if (status == PlaybackStatus::Paused) {
            std::cout << "Resuming audio: " << mediaInfo.title << std::endl;
        } else {
            std::cout << "Playing audio: " << mediaInfo.title << std::endl;
        }
        
        status = PlaybackStatus::Playing;
    }
    
    void pause() override {
        if (status == PlaybackStatus::Playing) {
            std::cout << "Audio paused" << std::endl;
            status = PlaybackStatus::Paused;
        }
    }
    
    void stop() override {
        if (status != PlaybackStatus::Stopped) {
            std::cout << "Audio stopped" << std::endl;
            status = PlaybackStatus::Stopped;
            currentPosition = 0;
        }
    }
    
    void seekTo(int position) override {
        if (position >= 0 && position < mediaInfo.duration) {
            currentPosition = position;
            std::cout << "Seek to " << formatTime(position) << std::endl;
        } else {
            std::cout << "Invalid position" << std::endl;
        }
    }
    
    PlaybackStatus getStatus() const override {
        return status;
    }
    
    MediaInfo getMediaInfo() const override {
        return mediaInfo;
    }
    
    // Các phương thức đặc thù của AudioPlayer
    void setVolume(int newVolume) {
        if (newVolume >= 0 && newVolume <= 100) {
            volume = newVolume;
            if (newVolume > 0) {
                isMuted = false;
            }
            std::cout << "Volume set to " << volume << "%" << std::endl;
        }
    }
    
    int getVolume() const {
        return isMuted ? 0 : volume;
    }
    
    void mute() {
        isMuted = true;
        std::cout << "Audio muted" << std::endl;
    }
    
    void unmute() {
        isMuted = false;
        std::cout << "Audio unmuted, volume: " << volume << "%" << std::endl;
    }
    
    bool isMutedState() const {
        return isMuted;
    }
    
    std::string formatTime(int seconds) const {
        int minutes = seconds / 60;
        int secs = seconds % 60;
        return std::to_string(minutes) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
    }
    
    std::string getPlaybackInfo() const {
        return formatTime(currentPosition) + " / " + formatTime(mediaInfo.duration);
    }
};

// Lớp cụ thể: Video Player
class VideoPlayer : public MediaPlayer {
private:
    // Thuộc tính được đóng gói (Encapsulation)
    int volume; // 0-100
    bool isMuted;
    int brightness; // 0-100
    int contrast; // 0-100
    std::vector<std::string> supportedFormats;
    bool isFullscreen;
    
    // Phương thức private
    void extractMetadata(const std::string& path) {
        // Mô phỏng trích xuất metadata từ tệp video
        mediaInfo.title = getFileName(path);
        mediaInfo.title = mediaInfo.title.substr(0, mediaInfo.title.find_last_of("."));
        
        // Giả lập trích xuất metadata
        if (path.find("movie") != std::string::npos) {
            mediaInfo.artist = "Example Director";
            mediaInfo.year = 2020;
            mediaInfo.duration = 5400 + rand() % 3600; // 90-150 phút
        } else {
            mediaInfo.artist = "Unknown";
            mediaInfo.duration = 120 + rand() % 480; // 2-10 phút
        }
    }
    
    bool isFormatSupported(const std::string& extension) const {
        return std::find(supportedFormats.begin(), supportedFormats.end(), extension) != supportedFormats.end();
    }

public:
    VideoPlayer() : volume(50), isMuted(false), brightness(50), contrast(50), isFullscreen(false) {
        status = PlaybackStatus::Stopped;
        currentPosition = 0;
        
        // Định dạng được hỗ trợ
        supportedFormats = {"mp4", "avi", "mkv", "mov", "wmv"};
        
        mediaInfo.type = MediaType::Video;
    }
    
    bool loadMedia(const std::string& path) override {
        std::string extension = getFileExtension(path);
        
        // Kiểm tra định dạng được hỗ trợ
        if (!isFormatSupported(extension)) {
            std::cout << "Unsupported video format: " << extension << std::endl;
            return false;
        }
        
        currentFilePath = path;
        currentPosition = 0;
        status = PlaybackStatus::Stopped;
        
        // Trích xuất thông tin tệp
        extractMetadata(path);
        
        std::cout << "Loaded video: " << mediaInfo.title << std::endl;
        return true;
    }
    
    void play() override {
        if (currentFilePath.empty()) {
            std::cout << "No video file loaded" << std::endl;
            return;
        }
        
        if (status == PlaybackStatus::Paused) {
            std::cout << "Resuming video: " << mediaInfo.title << std::endl;
        } else {
            std::cout << "Playing video: " << mediaInfo.title << std::endl;
        }
        
        status = PlaybackStatus::Playing;
    }
    
    void pause() override {
        if (status == PlaybackStatus::Playing) {
            std::cout << "Video paused" << std::endl;
            status = PlaybackStatus::Paused;
        }
    }
    
    void stop() override {
        if (status != PlaybackStatus::Stopped) {
            std::cout << "Video stopped" << std::endl;
            status = PlaybackStatus::Stopped;
            currentPosition = 0;
        }
    }
    
    void seekTo(int position) override {
        if (position >= 0 && position < mediaInfo.duration) {
            currentPosition = position;
            std::cout << "Seek to " << formatTime(position) << std::endl;
        } else {
            std::cout << "Invalid position" << std::endl;
        }
    }
    
    PlaybackStatus getStatus() const override {
        return status;
    }
    
    MediaInfo getMediaInfo() const override {
        return mediaInfo;
    }
    
    // Các phương thức đặc thù của VideoPlayer
    void setVolume(int newVolume) {
        if (newVolume >= 0 && newVolume <= 100) {
            volume = newVolume;
            if (newVolume > 0) {
                isMuted = false;
            }
            std::cout << "Volume set to " << volume << "%" << std::endl;
        }
    }
    
    void setBrightness(int value) {
        if (value >= 0 && value <= 100) {
            brightness = value;
            std::cout << "Brightness set to " << brightness << "%" << std::endl;
        }
    }
    
    void setContrast(int value) {
        if (value >= 0 && value <= 100) {
            contrast = value;
            std::cout << "Contrast set to " << contrast << "%" << std::endl;
        }
    }
    
    void toggleFullscreen() {
        isFullscreen = !isFullscreen;
        std::cout << "Fullscreen mode: " << (isFullscreen ? "On" : "Off") << std::endl;
    }
    
    bool getFullscreenMode() const {
        return isFullscreen;
    }
    
    std::string formatTime(int seconds) const {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        int secs = seconds % 60;
        
        if (hours > 0) {
            return std::to_string(hours) + ":" + 
                  (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + 
                  (secs < 10 ? "0" : "") + std::to_string(secs);
        } else {
            return std::to_string(minutes) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
        }
    }
    
    std::string getPlaybackInfo() const {
        return formatTime(currentPosition) + " / " + formatTime(mediaInfo.duration);
    }
    
    std::string getVideoSettings() const {
        return "Brightness: " + std::to_string(brightness) + "%, Contrast: " + std::to_string(contrast) + "%";
    }
};

// Lớp quản lý hệ thống media
class MediaSystem {
private:
    AudioPlayer audioPlayer;
    VideoPlayer videoPlayer;
    MediaPlayer* activePlayer; // Trỏ tới người chơi đang hoạt động
    
    // Playlist
    std::vector<std::string> playlist;
    int currentPlaylistIndex;
    
    // Thông tin hiển thị
    bool displayEnabled;
    bool isVehicleMoving;

public:
    MediaSystem() : activePlayer(nullptr), currentPlaylistIndex(-1), 
                   displayEnabled(true), isVehicleMoving(false) {}
    
    void loadAudioFile(const std::string& path) {
        if (audioPlayer.loadMedia(path)) {
            activePlayer = &audioPlayer;
        }
    }
    
    void loadVideoFile(const std::string& path) {
        if (isVehicleMoving) {
            std::cout << "Cannot play video while vehicle is moving" << std::endl;
            return;
        }
        
        if (videoPlayer.loadMedia(path)) {
            activePlayer = &videoPlayer;
        }
    }
    
    void addToPlaylist(const std::string& path) {
        playlist.push_back(path);
        std::cout << "Added to playlist: " << path << std::endl;
        
        // Nếu đây là mục đầu tiên, tải nó
        if (playlist.size() == 1) {
            currentPlaylistIndex = 0;
            loadMediaFromPlaylist(currentPlaylistIndex);
        }
    }
    
    void clearPlaylist() {
        playlist.clear();
        currentPlaylistIndex = -1;
        std::cout << "Playlist cleared" << std::endl;
    }
    
    void nextTrack() {
        if (playlist.empty()) {
            std::cout << "Playlist is empty" << std::endl;
            return;
        }
        
        currentPlaylistIndex = (currentPlaylistIndex + 1) % playlist.size();
        loadMediaFromPlaylist(currentPlaylistIndex);
        play();
    }
    
    void previousTrack() {
        if (playlist.empty()) {
            std::cout << "Playlist is empty" << std::endl;
            return;
        }
        
        currentPlaylistIndex = (currentPlaylistIndex - 1 + playlist.size()) % playlist.size();
        loadMediaFromPlaylist(currentPlaylistIndex);
        play();
    }
    
    void play() {
        if (activePlayer) {
            activePlayer->play();
        } else {
            std::cout << "No media selected" << std::endl;
        }
    }
    
    void pause() {
        if (activePlayer) {
            activePlayer->pause();
        } else {
            std::cout << "No media selected" << std::endl;
        }
    }
    
    void stop() {
        if (activePlayer) {
            activePlayer->stop();
        } else {
            std::cout << "No media selected" << std::endl;
        }
    }
    
    void setVolume(int volume) {
        audioPlayer.setVolume(volume);
        videoPlayer.setVolume(volume);
    }
    
    void setDisplayEnabled(bool enabled) {
        displayEnabled = enabled;
        std::cout << "Display " << (enabled ? "enabled" : "disabled") << std::endl;
    }
    
    void setVehicleMovingStatus(bool moving) {
        isVehicleMoving = moving;
        std::cout << "Vehicle moving status: " << (moving ? "Moving" : "Stopped") << std::endl;
        
        // Nếu xe đang di chuyển và đang phát video, tạm dừng video
        if (moving && activePlayer == &videoPlayer && 
            videoPlayer.getStatus() == PlaybackStatus::Playing) {
            std::cout << "Video playback paused for safety" << std::endl;
            videoPlayer.pause();
        }
    }
    
    void displayCurrentMedia() {
        if (!activePlayer) {
            std::cout << "No media playing" << std::endl;
            return;
        }
        
        MediaInfo info = activePlayer->getMediaInfo();
        
        std::cout << "\n===== Current Media =====" << std::endl;
        std::cout << "Title: " << info.title << std::endl;
        
        if (!info.artist.empty()) {
            std::cout << "Artist: " << info.artist << std::endl;
        }
        
        if (!info.album.empty() && info.type == MediaType::Audio) {
            std::cout << "Album: " << info.album << std::endl;
        }
        
        if (info.year > 0) {
            std::cout << "Year: " << info.year << std::endl;
        }
        
        std::cout << "Type: " << (info.type == MediaType::Audio ? "Audio" : "Video") << std::endl;
        
        PlaybackStatus status = activePlayer->getStatus();
        std::cout << "Status: ";
        switch (status) {
            case PlaybackStatus::Playing:
                std::cout << "Playing";
                break;
            case PlaybackStatus::Paused:
                std::cout << "Paused";
                break;
            case PlaybackStatus::Stopped:
                std::cout << "Stopped";
                break;
            case PlaybackStatus::Error:
                std::cout << "Error";
                break;
        }
        std::cout << std::endl;
        
        // Display playback information
        if (activePlayer == &audioPlayer) {
            std::cout << "Playback: " << audioPlayer.getPlaybackInfo() << std::endl;
            std::cout << "Volume: " << audioPlayer.getVolume() << "%" << 
                     (audioPlayer.isMutedState() ? " (Muted)" : "") << std::endl;
        } 
        else if (activePlayer == &videoPlayer) {
            std::cout << "Playback: " << videoPlayer.getPlaybackInfo() << std::endl;
            std::cout << videoPlayer.getVideoSettings() << std::endl;
            std::cout << "Fullscreen: " << (videoPlayer.getFullscreenMode() ? "Yes" : "No") << std::endl;
        }
        
        // Display playlist information
        if (!playlist.empty()) {
            std::cout << "\nPlaylist (" << currentPlaylistIndex + 1 << "/" << playlist.size() << ")" << std::endl;
            for (size_t i = 0; i < playlist.size(); ++i) {
                if (i == currentPlaylistIndex) {
                    std::cout << "> ";
                } else {
                    std::cout << "  ";
                }
                std::cout << i + 1 << ". " << playlist[i] << std::endl;
            }
        }
    }

private:
    void loadMediaFromPlaylist(int index) {
        if (index >= 0 && index < static_cast<int>(playlist.size())) {
            std::string path = playlist[index];
            std::string extension = path.substr(path.find_last_of(".") + 1);
            
            // Tự động xác định loại media
            if (extension == "mp3" || extension == "wav" || extension == "aac" || 
                extension == "flac" || extension == "ogg") {
                loadAudioFile(path);
            } 
            else if (extension == "mp4" || extension == "avi" || extension == "mkv" || 
                     extension == "mov" || extension == "wmv") {
                loadVideoFile(path);
            }
            else {
                std::cout << "Unsupported file format: " << extension << std::endl;
            }
        }
    }
};

// Hàm main để kiểm thử
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(static_cast<unsigned int>(time(nullptr)));
    
    MediaSystem carMediaSystem;
    
    // Thêm các tệp vào danh sách phát
    carMediaSystem.addToPlaylist("music/song1.mp3");
    carMediaSystem.addToPlaylist("music/song2.mp3");
    carMediaSystem.addToPlaylist("videos/movie1.mp4");
    
    // Phát media
    carMediaSystem.play();
    carMediaSystem.displayCurrentMedia();
    
    // Thiết lập âm lượng
    carMediaSystem.setVolume(70);
    
    // Chuyển đến bài tiếp theo
    carMediaSystem.nextTrack();
    carMediaSystem.displayCurrentMedia();
    
    // Mô phỏng xe đang di chuyển - sẽ ảnh hưởng đến khả năng phát video
    carMediaSystem.setVehicleMovingStatus(true);
    
    // Thử chuyển đến video
    carMediaSystem.nextTrack();
    carMediaSystem.displayCurrentMedia();
    
    // Xe dừng lại - có thể phát video
    carMediaSystem.setVehicleMovingStatus(false);
    carMediaSystem.play();
    carMediaSystem.displayCurrentMedia();
    
    return 0;
}