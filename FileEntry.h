//
// Created by julian on 5/6/25.
//

#ifndef FILEENTRY_H
#define FILEENTRY_H

#include <gtkmm.h>

#include "FileManager.h"

extern FileManager fm;
class FileEntry : public Gtk::EventBox{
    File file;
    public:
    FileEntry(File f);
    ~FileEntry() override = default;
    Gtk::Label label;
protected:
    bool on_box_hover(GdkEventCrossing *event);
    bool on_box_unhover(GdkEventCrossing *event);
    bool on_event_box_click(GdkEventButton* event);

};



#endif //FILEENTRY_H
