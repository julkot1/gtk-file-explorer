#ifndef TOP_PANEL_H
#define TOP_PANEL_H

#include <gtkmm.h>

#include "FileManager.h"
#include "FilesSpace.h"

extern FileManager fm;

class TopPanel : public Gtk::Box {
public:
    TopPanel(FilesSpace *files_space);
    ~TopPanel() override = default;

    void set_label_text(const std::string& text);

protected:
    // Event handlers for buttons
    void on_left_button_clicked();
    void on_right_button_clicked();
    void on_parent_button_clicked();

private:
    Gtk::Label label; // Label widget
    Gtk::Button left_button; // Left arrow button
    Gtk::Button right_button; // Right arrow button
    Gtk::Button parent_button;
    FilesSpace *files_space;
};

#endif // TOP_PANEL_H
