#include <iostream>
#include <string>

class PlaylistImporter {
private:
    // Các bước chung (cố định)
    void open(const char* path) { std::cout << "1. Mo file: " << path << std::endl; }
    void addToLibrary() { std::cout << "4. Dang them cac bai hat hop le vao thu vien...\n"; }
    void close() { std::cout << "5. Dong file. Hoan tat!\n"; }

protected:
    // Các bước thay đổi (phải được lớp con triển khai)
    virtual bool parseContents() = 0;
    virtual bool validateSongs() = 0;

public:
    virtual ~PlaylistImporter() {}

    // 2. TEMPLATE METHOD: Dinh nghia khung thuat toan (Khong duoc override)
    void importFromFile(const char* path) {
        open(path);
        if (parseContents()) { // Buoc tuy chinh 1
            if (validateSongs()) { // Buoc tuy chinh 2
                addToLibrary();
            }
        }
        close();
    }
};

// 4. Implement Concrete Classes
class TxtPlaylistImporter : public PlaylistImporter {
protected:
    bool parseContents() override {
        std::cout << "2. [TXT] Doc tung dong de lay duong dan file.\n";
        return true;
    }
    bool validateSongs() override {
        std::cout << "3. [TXT] Kiem tra duong dan file co ton tai hay khong.\n";
        return true;
    }
};

class XmlPlaylistImporter : public PlaylistImporter {
protected:
    bool parseContents() override {
        std::cout << "2. [XML] Phan tich cac the <path> va <title>.\n";
        return true;
    }
    bool validateSongs() override {
        std::cout << "3. [XML] Kiem tra checksum va metadata cua bai hat.\n";
        return true;
    }
};

int main() {
    PlaylistImporter* importer = nullptr;

    std::cout << "--- NHAP FILE TXT ---\n";
    importer = new TxtPlaylistImporter();
    importer->importFromFile("favorites.txt");
    delete importer;

    std::cout << "\n--- NHAP FILE XML ---\n";
    importer = new XmlPlaylistImporter();
    importer->importFromFile("rock_playlist.xml");
    delete importer;

    return 0;
}