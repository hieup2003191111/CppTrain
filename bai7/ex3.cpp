#include <iostream>  
#include <string>
using namespace std;
struct Song{
    string title;
    double volume = 0;
    void normalize(){volume = 5;};
};
void normalizeQueue(Song (&queue)[3], int size) {
    cout << "\n--- Dang thuc hien normalizeQueue ---" << endl;

    // PHIÊN BẢN LỖI: s là một BẢN SAO (Copy).
    // Moi thay doi tren 's' se bien mat khi vong lap sang buoc tiep theo.
    for (Song s : queue) { 
        s.normalize(); 
    }
}

void normalizeQueue_FIXED(Song (&queue)[3], int size) {
    cout << "\n--- Dang thuc hien normalizeQueue_FIXED (Dung tham chieu) ---" << std::endl;

    // PHIÊN BẢN ĐÚNG: Them dau '&' de 's' tro thanh THAM CHIẾU.
    // Luc nay 's' chinh la phan tu dang nam trong mang goc.
    for (Song &s : queue) { 
        s.normalize(); 
    }
}

int main() {
    Song myQueue[3] = {{"Bai hat 1"}, {"Bai hat 2"}, {"Bai hat 3"}};

    // 1. Thu nghiem voi ham loi
    normalizeQueue(myQueue, 3);
    std::cout << "Ket qua sau khi dung ban sao: " << myQueue[0].volume << " dB (Khong doi)" << std::endl;

    // 2. Thu nghiem voi ham da sua
    normalizeQueue_FIXED(myQueue, 3);
    std::cout << "Ket qua sau khi dung tham chieu: " << myQueue[0].volume << " dB (Da thay doi!)" << std::endl;

    return 0;
}