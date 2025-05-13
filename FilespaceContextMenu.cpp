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
#include <giomm.h>
extern MyWindow *window_ptr;
extern FileManager fm;

FilespaceContextMenu::FilespaceContextMenu() {
   create_menu();
}
void FilespaceContextMenu::create_menu() {
   // Create the "New" menu item with a submenu
    new_menu_item = Gtk::manage(new Gtk::MenuItem("New", true));
    new_submenu = Gtk::manage(new Gtk::Menu());

    new_file_item = Gtk::manage(new Gtk::MenuItem("File", true));
    new_folder_item = Gtk::manage(new Gtk::MenuItem("Folder", true));


    new_file_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::show_new_file_dialog));

    new_folder_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::show_new_folder_dialog));


    new_submenu->append(*new_file_item);
    new_submenu->append(*new_folder_item);

    select_all_item = Gtk::manage(new Gtk::MenuItem("Select all", true));
    select_all_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::select_all));

    copy_files_item = Gtk::manage(new Gtk::MenuItem("Copy", true));
    copy_files_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::copy_files));


    paste_files_item = Gtk::manage(new Gtk::MenuItem("Paste", true));
    paste_files_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::paste_files));


    cut_files_item = Gtk::manage(new Gtk::MenuItem("Cut", true));
    delete_files_item = Gtk::manage(new Gtk::MenuItem("Delete", true));
    delete_files_item->signal_activate().connect(sigc::mem_fun(*this, &FilespaceContextMenu::delete_files));

    new_menu_item->set_submenu(*new_submenu);


    append(*new_menu_item);
    auto separator = Gtk::manage(new Gtk::SeparatorMenuItem());
    append(*separator);
    append(*select_all_item);
    append(*copy_files_item);
    append(*paste_files_item);
    append(*cut_files_item);
    append(*delete_files_item);

}

void FilespaceContextMenu::paste_files() {
    auto clipboard = Gtk::Clipboard::get();  // Get the clipboard
    auto destination_dir = fm.getPath().string();
    clipboard->request_text([destination_dir](const Glib::ustring& text) {
        std::istringstream stream(text);
        std::string operation;
        std::getline(stream, operation);  // "copy" or "cut"

        std::string uri;
        while (std::getline(stream, uri)) {
            if (uri.empty()) continue;

            // Extract the file from the URI
            auto src_file = Gio::File::create_for_uri(uri);
            auto filename = src_file->get_basename();
            auto dest_file = Gio::File::create_for_path(destination_dir + "/" + filename);

            try {
                if (operation == "cut") {
                    src_file->move(dest_file, Gio::FILE_COPY_OVERWRITE);  // Cut operation
                    std::cout << "Moved: " << filename << "\n";
                } else {
                    src_file->copy(dest_file, Gio::FILE_COPY_OVERWRITE);  // Copy operation
                    std::cout << "Copied: " << filename << "\n";
                }
            } catch (const Glib::Error& e) {
                std::cerr << "Error handling file " << filename << ": " << e.what() << "\n";
            }
        }
    });
    window_ptr->update_files();
}

void FilespaceContextMenu::copy_files() {
    std::string clipboard_data = "copy\n";
    for (const auto& path : window_ptr->selected) {
        Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(path->file.path);
        clipboard_data += file->get_uri() + "\n";
    }
    std::cout << clipboard_data;
    auto clipboard = Gtk::Clipboard::get();
    clipboard->set_text(clipboard_data);
}


void remove_directory_recursively(const std::string& dir_path) {
    try {
        // Check if the directory exists
        if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
            // Iterate through the directory and remove files/subdirectories
            for (const auto& entry : fs::directory_iterator(dir_path)) {
                const fs::path& child_path = entry.path();
                if (fs::is_directory(child_path)) {
                    // If it's a directory, recursively call the function
                    remove_directory_recursively(child_path);
                } else {
                    // If it's a file, remove it
                    fs::remove(child_path);
                    std::cout << "Removed file: " << child_path << std::endl;
                }
            }

            // Now that all children are removed, remove the empty directory
            fs::remove(dir_path);
            std::cout << "Removed directory: " << dir_path << std::endl;
        } else {
            std::cerr << "Directory does not exist or is not a directory: " << dir_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error removing directory: " << e.what() << std::endl;
    }
}

void FilespaceContextMenu::delete_files() {
    for (auto f : window_ptr->selected) {

        try {
            if(f->file.type == DIRECTORY_TYPE) {
                remove_directory_recursively(f->file.path);
            }
            else if (std::filesystem::remove(f->file.path)) {
                std::cout << "File deleted successfully.\n";
            } else {
                std::cout << "File not found or couldn't be deleted.\n";
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    window_ptr->update_files();
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

void FilespaceContextMenu::select_all() {
    window_ptr->files_space.selectAll();
}

void FilespaceContextMenu::show_at_pointer(GdkEventButton *button_event) {
    show_all();
    popup_at_pointer(reinterpret_cast<GdkEvent*>(button_event));
}
