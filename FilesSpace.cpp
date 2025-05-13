#include "FilesSpace.h"
#include <iostream>

#include "MyWindow.h"


extern MyWindow* window_ptr;
FilesSpace::FilesSpace() : label("sfdfdf") {
    set_margin_top(10);
    set_margin_bottom(10);
    set_margin_left(10);
    set_margin_right(10);
    set_hexpand(true);

    grid.set_row_spacing(2);
    grid.set_column_spacing(20);
    grid.set_margin_top(10);
    grid.set_valign(Gtk::ALIGN_START);
    grid.set_max_children_per_line(10);
    grid.set_selection_mode(Gtk::SELECTION_NONE);
    grid.set_hexpand(true);
    grid.set_vexpand(true);

    // Ensure the event mask is set for the whole widget, not just a part of it
    set_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this, &FilesSpace::on_box_button_press), false);

    add(grid);
    show_all_children();
}

bool FilesSpace::on_box_button_press(GdkEventButton* button_event) {
    if ((button_event->type == GDK_BUTTON_PRESS) && (button_event->button == 3)) { // Right-click
        // Create the context menu items
        context_menu.show_at_pointer(button_event);
        return true; // Event handled (don't propagate further)
    }

    return true; // Event not handled (let others handle it)
}

void FilesSpace::update(std::vector<File> &files) {
    // Clear existing entries in the grid
    for (auto* child : grid.get_children()) {
        grid.remove(*child);
    }

    this->files.clear();  // Clear the current files list

    // Add new file entries to the grid
    for (auto file : files) {
        auto entry = std::make_unique<FileEntry>(file);
        grid.add(*entry);
        this->files.push_back(std::move(entry));
    }

    show_all_children();  // Ensure everything is displayed
}
void FilesSpace::selectAll() {

    window_ptr->selected.clear();
    for (std::shared_ptr<FileEntry> entry : files) {
        entry.get()->get_style_context()->add_class("selected");
        window_ptr->selected.push_back(entry.get());

    }
}
