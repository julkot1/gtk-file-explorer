//
// Created by julian on 5/6/25.
//

#ifndef FILEEXPLOERMANAGER_H
#define FILEEXPLOERMANAGER_H
#include <string>

#include <filesystem>
#include <vector>

#include "File.h"

namespace fs = std::filesystem;


class FileManager {
    fs::path path;
    std::vector<fs::path> history;

    int currentIndex = 0;
    void addToHistory();
public:
    std::vector<File *> filesSelected;
    bool selectMode = false;
    explicit FileManager(std::string path);

    fs::path getPath();
    void setPath(fs::path path);
    void setParent();
    fs::path getPrevPath();
    fs::path getNextPath();

    std::vector<File> getFiles();

};



#endif //FILEEXPLOERMANAGER_H
