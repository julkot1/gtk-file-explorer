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

    set_size_request(100,100);
    set_halign(Gtk::ALIGN_CENTER);
    set_valign(Gtk::ALIGN_CENTER);

    vbox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    vbox.set_spacing(4);
    vbox.set_halign(Gtk::ALIGN_CENTER);
    vbox.set_valign(Gtk::ALIGN_CENTER);

    vbox.pack_start(image, Gtk::PACK_SHRINK);
    vbox.pack_start(label, Gtk::PACK_SHRINK);


    label.set_line_wrap(true);
    label.set_line_wrap_mode(Pango::WRAP_CHAR);
    label.set_max_width_chars(15);
    label.set_text(f.name);
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

    if (event->button == 1 && event->type == GDK_2BUTTON_PRESS) {

        if (file.type == DIRECTORY_TYPE) {
            fm.setPath(fm.getPath().string()+"/"+file.name);
            window_ptr->update_files();
        }


    } else if (event->button == 2) { // Middle mouse button
        std::cout << "Middle click detected!" << std::endl;
    } if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) { // Right-click
        // Create the context menu items
        context_menu = Gtk::Menu();

        Gtk::MenuItem* item1 = Gtk::manage(new Gtk::MenuItem("Optssdsdsdsdion 1", true));
        //Gtk::MenuItem* item2 = Gtk::manage(new Gtk::MenuItem("Optsdsdion 2", true));

        item1->signal_activate().connect([]() {
            std::cout << "Option 1 clicked\n";
        });


        context_menu.append(*item1);
       // context_menu.append(*item2);
        context_menu.show_all();

        // Show menu at mouse position (make sure it shows at the location of the click)
        context_menu.popup_at_pointer(reinterpret_cast<GdkEvent*>(event));
        return true; // Event handled (don't propagate further)
    }

    return false;
}