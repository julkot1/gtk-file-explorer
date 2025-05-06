//
// Created by julian on 5/6/25.
//

#ifndef FILESSPACE_H
#define FILESSPACE_H


#include <gtkmm.h>

#include "FileEntry.h"


class FilesSpace :public Gtk::Box{
public:
    FilesSpace();
    ~FilesSpace() override = default;
    void update(std::vector<File> &files);
private:
    Gtk::Label label;
    Gtk::FlowBox grid;
    std::vector<std::unique_ptr<FileEntry>> files;
};



#endif //FILESSPACE_H
