#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <stdexcept>

template <typename T>
class Playlist {
private:
    std::vector<T> items;
    int currentIndex;

public:
    Playlist() : currentIndex(0) {}

    // Thêm một mục vào danh sách
    void addItem(const T& item) {
        items.push_back(item);
    }

    // Kiểm tra xem có mục kế tiếp không
    bool hasNext() const {
        return (currentIndex + 1) < items.size();
    }

    // Chuyển sang mục tiếp theo
    void next() {
        if (hasNext()) {
            currentIndex++;
        }
    }

    // Lấy mục hiện tại
    T& getCurrentItem() {
        if (items.empty()) {
            throw std::out_of_range("Playlist is empty!");
        }
        return items[currentIndex];
    }

    // Xóa mục hiện tại
    void removeCurrent() {
        if (!items.empty()) {
            items.erase(items.begin() + currentIndex);
            // Điều chỉnh index nếu nó vượt quá kích thước sau khi xóa
            if (currentIndex >= items.size() && !items.empty()) {
                currentIndex = items.size() - 1;
            }
        }
    }
    
    int size() const { return items.size(); }
};

#endif