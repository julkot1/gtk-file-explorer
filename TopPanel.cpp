#include "TopPanel.h"
#include <iostream>

#include "MyWindow.h"

extern MyWindow* window_ptr;
TopPanel::TopPanel(FilesSpace *files_space)
    : left_button("←"), right_button("→"), parent_button("^"), files_space(files_space)// Initialize the buttons with arrows
{
    // Set the orientation of the box to horizontal
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    set_spacing(10); // Set space between the widgets

    // Set margins for the box
    set_margin_top(10);
    set_margin_bottom(10);
    set_margin_start(10);
    set_margin_end(10);

    // Initialize the label text
    label.set_text(fm.getPath().c_str());
    label.set_padding(10, 10); // Add some padding around the label

    // Pack the left arrow button into the box
    pack_start(left_button, Gtk::PACK_SHRINK);
    left_button.signal_clicked().connect(sigc::mem_fun(*this, &TopPanel::on_left_button_clicked));

    // Pack the right arrow button into the box
    pack_start(right_button, Gtk::PACK_SHRINK);
    right_button.signal_clicked().connect(sigc::mem_fun(*this, &TopPanel::on_right_button_clicked));

    pack_start(parent_button, Gtk::PACK_SHRINK);
    parent_button.signal_clicked().connect(sigc::mem_fun(*this, &TopPanel::on_parent_button_clicked));
    pack_start(label, Gtk::PACK_SHRINK);
    show_all_children();  // Make sure everything is visible
}

// Function to set the label text
void TopPanel::set_label_text(const std::string& text) {
    label.set_text(text);
}

// Event handler for left arrow button click
void TopPanel::on_left_button_clicked() {
    fs::path path = fm.getNextPath();
    this->update();
    window_ptr->update_files();
}

// Event handler for right arrow button click
void TopPanel::on_right_button_clicked() {
    fs::path path = fm.getPrevPath();
    this->update();
    window_ptr->update_files();

}

void TopPanel::update() {
    label.set_text(fm.getPath().c_str());
    auto f = fm.getFiles();
    files_space->update(f);

}
void TopPanel::on_parent_button_clicked() {
    fm.setParent();
    this->update();
    window_ptr->update_files();

}
