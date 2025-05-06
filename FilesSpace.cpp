//
// Created by julian on 5/6/25.
//

#include "FilesSpace.h"


FilesSpace::FilesSpace() : label("sfdfdf") {
    set_margin_top(10);
    set_margin_bottom(10);
    set_margin_left(10);
    set_margin_right(10);

    grid.set_row_spacing(2);
    grid.set_column_spacing(20);;
    grid.set_margin_top(10);
    grid.set_valign(Gtk::ALIGN_START);
    grid.set_max_children_per_line(10);
    grid.set_selection_mode(Gtk::SELECTION_NONE);
    grid.set_hexpand(true);



    add(grid);
    show_all_children();
}

void FilesSpace::update(std::vector<File> &files) {
    for (auto* child : grid.get_children()) {
        grid.remove(*child);
    }
    this->files.clear();
    for (auto file : files) {
        auto entry = std::make_unique<FileEntry>(file);
        grid.add(*entry);
        this->files.push_back(std::move(entry));
    }
    show_all_children();
}

