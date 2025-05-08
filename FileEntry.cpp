//
// Created by julian on 5/6/25.
//

#include "FileEntry.h"

#include <iostream>

#include "MyWindow.h"
extern MyWindow *window_ptr;
FileEntry::FileEntry(File f): file(f), label("") {


    if (f.type == DIRECTORY_TYPE)image.set_from_icon_name("folder", Gtk::ICON_SIZE_DIALOG);
    else if (f.type == FILE_TYPE)
        image.set_from_icon_name("file", Gtk::ICON_SIZE_DIALOG);

    set_hexpand(true);
    set_events(Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK);
    signal_enter_notify_event().connect(sigc::mem_fun(*this, &FileEntry::on_box_hover));
    signal_leave_notify_event().connect(sigc::mem_fun(*this, &FileEntry::on_box_unhover));
    signal_button_press_event().connect(sigc::mem_fun(*this, &FileEntry::on_event_box_click));


    label.set_text(f.name);
    vbox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    vbox.set_spacing(4);
    vbox.set_halign(Gtk::ALIGN_CENTER);

    vbox.pack_start(image, Gtk::PACK_SHRINK);
    vbox.pack_start(label, Gtk::PACK_SHRINK);

    label.set_justify(Gtk::JUSTIFY_CENTER);
    label.set_halign(Gtk::ALIGN_CENTER);

    add(vbox);

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
    if (event->button == 1 && event->type == GDK_2BUTTON_PRESS) { // Left mouse button

        if (file.type == DIRECTORY_TYPE) {
            fm.setPath(fm.getPath().string()+"/"+file.name);
            window_ptr->update_files();
        }


    } else if (event->button == 2) { // Middle mouse button
        std::cout << "Middle click detected!" << std::endl;
    } else if (event->button == 3) { // Right mouse button
        std::cout << "Right click detected!" << std::endl;
    }

    // Return false to allow the event to propagate (e.g., clicking a button inside EventBox)
    return false;
}