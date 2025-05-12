//
// Created by julian on 5/6/25.
//

#ifndef FILESSPACE_H
#define FILESSPACE_H


#include <gtkmm.h>

#include "FileEntry.h"
#include "FilespaceContextMenu.h"


class FilesSpace :public Gtk::Paned{
public:
    FilesSpace();
    ~FilesSpace() override = default;
    void update(std::vector<File> &files);
private:
    Gtk::Label label;
    Gtk::FlowBox grid;
    std::vector<std::unique_ptr<FileEntry>> files;
    FilespaceContextMenu context_menu;
    bool on_box_button_press(GdkEventButton* button_event);
};



#endif //FILESSPACE_H
