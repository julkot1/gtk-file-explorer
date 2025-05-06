//
// Created by julian on 5/6/25.
//

#include "FileEntry.h"

#include <iostream>

FileEntry::FileEntry(File f): file(f), label("") {



    set_hexpand(true);
    set_events(Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK); // Important for hover
    signal_enter_notify_event().connect(sigc::mem_fun(*this, &FileEntry::on_box_hover));
    signal_leave_notify_event().connect(sigc::mem_fun(*this, &FileEntry::on_box_unhover));
    signal_button_press_event().connect(sigc::mem_fun(*this, &FileEntry::on_event_box_click));


    label.set_text(f.name + (f.type == DIRECTORY_TYPE?"[D]": "[F]"));

    add(label);

    show_all_children();
}

bool FileEntry::on_box_hover(GdkEventCrossing* event) {
    get_style_context()->add_class("hovered");
    return false;
}

bool FileEntry::on_box_unhover(GdkEventCrossing* event) {
    get_style_context()->remove_class("hovered");
    return false;
}
bool FileEntry::on_event_box_click(GdkEventButton* event) {
    // Check which button was pressed
    if (event->button == 1) { // Left mouse button
        std::cout << "Left click detected!" << std::endl;
        fm.setPath(fm.getPath().string()+"/"+file.name);

    } else if (event->button == 2) { // Middle mouse button
        std::cout << "Middle click detected!" << std::endl;
    } else if (event->button == 3) { // Right mouse button
        std::cout << "Right click detected!" << std::endl;
    }

    // Return false to allow the event to propagate (e.g., clicking a button inside EventBox)
    return false;
}