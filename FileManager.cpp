//
// Created by julian on 5/6/25.
//

#include "FileManager.h"

#include <iostream>
#include <utility>

#include <algorithm>
#include <gtkmm/stock.h>

File::File(std::string name, const FileType type): name(std::move(name)), type(type) {

}
bool file_sorter(const File& a, const File& b) {
    if (a.type != b.type)
        return a.type == DIRECTORY_TYPE;
    return a.name < b.name;
}

FileManager::FileManager(std::string path){
    this->path = std::move(path);
}

fs::path FileManager::getPath() {
    return this->path;
}
void FileManager::setPath(fs::path path) {
    this->addToHistory();

    this->path = std::move(path);
}
void FileManager::setParent() {
    addToHistory();
    this->path = this->path.parent_path();
}

fs::path FileManager::getNextPath() {
    if (this->currentIndex+1 >= this->history.size()) {
        return this->path;
    }
    this->currentIndex++;
    this->path = this->history[this->currentIndex];
    return this->path;
}

fs::path FileManager::getPrevPath() {
    if (this->currentIndex-1 < 0) {
        return this->path;
    }
    this->currentIndex--;
    this->path = this->history[this->currentIndex];
    return this->path;
}
void FileManager::addToHistory() {
    if (this->history.size() ==0) {
        this->history.push_back(this->path);
        this->currentIndex ++;
        return;
    }
    if (this->history[currentIndex-1] != this->path) {
        this->history.push_back(this->path);
        this->currentIndex ++;
    }
}
std::vector<File> FileManager::getFiles() {
    std::vector<File> vec;
    if (fs::exists(this->path) && fs::is_directory(this->path)) {
        for (const auto& entry : fs::directory_iterator(this->path)) {
            vec.push_back(File(entry.path().filename().string(), entry.is_directory() ? DIRECTORY_TYPE : FILE_TYPE));
        }
    } else {
        std::cerr << "Invalid path: " << path << '\n';
    }
    std::sort(vec.begin(), vec.end(), file_sorter);

    return vec;

}

