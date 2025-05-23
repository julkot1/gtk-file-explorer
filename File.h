//
// Created by julian on 5/13/25.
//

#ifndef FILE_H
#define FILE_H
#include <string>

enum  FileType {
    DIRECTORY_TYPE,
    FILE_TYPE
};
class File {
public:
    std::string name;
    std::filesystem::path path;
    FileType type;

    File(std::string name, FileType type, std::string path);
    friend bool file_sorter(const File& a, const File& b);
};
#endif //FILE_H
