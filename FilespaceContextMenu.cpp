//
// Created by julian on 5/12/25.
//

#include "FilespaceContextMenu.h"

#include <iostream>

#include "MyWindow.h"
#include <fstream>      // for file creation
#include <filesystem>   // C++17 for path manipulation
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/messagedialog.h>

extern MyWindow *window_ptr;
extern FileManager fm;

FilespaceContextMenu::FilespaceContextMenu() {
   create_menu();
}
void FilespaceContextMenu::create_menu() {
   // Create the "New" menu item with a submenu
   new_menu_item = Gtk::manage(new Gtk::MenuItem("New", true));
   new_submenu = Gtk::manage(new Gtk::Menu());  // Submenu for "New"

   new_file_item = Gtk::manage(new Gtk::MenuItem("File", true));
   new_folder_item = Gtk::manage(new Gtk::MenuItem("Folder", true));


   new_file_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::show_new_file_dialog));

   new_folder_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::show_new_folder_dialog));


   new_submenu->append(*new_file_item);
   new_submenu->append(*new_folder_item);


   new_menu_item->set_submenu(*new_submenu);


   append(*new_menu_item);
}
void FilespaceContextMenu::show_new_folder_dialog() {
    Gtk::Dialog dialog("New Folder", true);
    dialog.set_transient_for(dynamic_cast<Gtk::Window &>(*this->get_toplevel()));
    dialog.set_modal(true);
    dialog.set_decorated(false);
    dialog.set_resizable(false);

    dialog.set_size_request(300, 100);

    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Create", Gtk::RESPONSE_OK);

    Gtk::Box* content_area = dialog.get_content_area();
    Gtk::Entry entry;
    entry.set_placeholder_text("Folder name...");
    content_area->pack_start(entry, Gtk::PACK_SHRINK, 10);
    entry.show();


    dialog.set_position(Gtk::WIN_POS_CENTER_ON_PARENT);

    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string folder_name = entry.get_text();
        if (!folder_name.empty()) {
            std::string path = fm.getPath().string()+"/" + folder_name;
            if (std::filesystem::exists(path)) {
                Gtk::MessageDialog error("Failed to create file.", false, Gtk::MESSAGE_ERROR);
                error.set_transient_for(dynamic_cast<Gtk::Window &>(*this->get_toplevel()));
                error.run();
                return;
            }
            if (std::filesystem::create_directory(path)) {
                window_ptr->update_files();
            } else {
                Gtk::MessageDialog error("Failed to create folder.", false, Gtk::MESSAGE_ERROR);
                error.set_transient_for(dynamic_cast<Gtk::Window &>(*this->get_toplevel()));
                error.run();
            }
        }
    }
}

void FilespaceContextMenu::show_new_file_dialog() {
    Gtk::Dialog dialog("New File", true);
    dialog.set_transient_for(dynamic_cast<Gtk::Window &>(*this->get_toplevel()));
    dialog.set_modal(true);
    dialog.set_decorated(false);
    dialog.set_resizable(false);

    dialog.set_size_request(300, 100);

    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Create", Gtk::RESPONSE_OK);

    Gtk::Box* content_area = dialog.get_content_area();
    Gtk::Entry entry;
    entry.set_placeholder_text("File name...");
    content_area->pack_start(entry, Gtk::PACK_SHRINK, 10);
    entry.show();


    dialog.set_position(Gtk::WIN_POS_CENTER_ON_PARENT);

    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string filename = entry.get_text();
        if (!filename.empty()) {
            std::string path = fm.getPath().string()+"/" + filename;
            if (std::filesystem::exists(path)) {
                Gtk::MessageDialog error("Failed to create file.", false, Gtk::MESSAGE_ERROR);
                error.set_transient_for(dynamic_cast<Gtk::Window &>(*this->get_toplevel()));
                error.run();
                return;
            }
            std::ofstream file(path);
            if (file.is_open()) {
                file.close();
                window_ptr->update_files();
            } else {
                Gtk::MessageDialog error("Failed to create file.", false, Gtk::MESSAGE_ERROR);
                error.set_transient_for(dynamic_cast<Gtk::Window &>(*this->get_toplevel()));
                error.run();
            }
        }
    }
}


void FilespaceContextMenu::show_at_pointer(GdkEventButton *button_event) {
    show_all();
    popup_at_pointer(reinterpret_cast<GdkEvent*>(button_event));
}
