//
// Created by julian on 5/12/25.
//

#ifndef FILESPACECONTEXTMENU_H
#define FILESPACECONTEXTMENU_H

#include <gtkmm.h>

class FilespaceContextMenu : public Gtk::Menu{
    public:
    FilespaceContextMenu();
    ~FilespaceContextMenu() override = default;
    void create_menu();
    void show_at_pointer(GdkEventButton* button_event);

private:
    Gtk::MenuItem* new_menu_item;
    Gtk::Menu* new_submenu;
    Gtk::MenuItem* new_file_item;
    Gtk::MenuItem* new_folder_item;


    void show_new_file_dialog();
    void show_new_folder_dialog();


};



#endif //FILESPACECONTEXTMENU_H
