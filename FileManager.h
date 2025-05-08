//
// Created by julian on 5/6/25.
//

#ifndef FILEEXPLOERMANAGER_H
#define FILEEXPLOERMANAGER_H
#include <string>

#include <filesystem>
#include <vector>



namespace fs = std::filesystem;

enum  FileType {
    DIRECTORY_TYPE,
    FILE_TYPE
};
class File {
public:
    std::string name;
    FileType type;

    File(std::string name, FileType type);
    friend bool file_sorter(const File& a, const File& b);
};
class FileManager {
    fs::path path;
    std::vector<fs::path> history;
    int currentIndex = 0;
    void addToHistory();
public:
    explicit FileManager(std::string path);

    fs::path getPath();
    void setPath(fs::path path);
    void setParent();
    fs::path getPrevPath();
    fs::path getNextPath();

    std::vector<File> getFiles();

};



#endif //FILEEXPLOERMANAGER_H
