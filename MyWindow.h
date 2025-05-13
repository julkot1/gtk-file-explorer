#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#pragma once
#include <gtkmm.h>

#include "FilesSpace.h"
#include "TopPanel.h"


class MyWindow : public Gtk::Window {
public:
    MyWindow();
    ~MyWindow() override = default;
    void update_files();
    std::vector<FileEntry *> selected;

protected:
    // Button click event handlers
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    bool on_button_release_event(GdkEventKey* event);
    bool on_button_press_event(GdkEventKey* event);


private:
    // Paned to split the window into left and right
    Gtk::Paned hpaned;

    // Left (Side) panel
    Gtk::ScrolledWindow scroll_left;
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Gtk::Button button1{"Button 1"};
    Gtk::Button button2{"Button 2"};
    Gtk::Button button3{"Button 3"};

    // Right (Center) panel
    Gtk::ScrolledWindow scroll_right;
    Gtk::Label label;

    // Top horizontal panel
    Gtk::Box vbox_top{Gtk::ORIENTATION_VERTICAL};  // The main vertical box for the window

    TopPanel top_panel;
    FilesSpace files_space;
};

#endif // MY_WINDOW_H
