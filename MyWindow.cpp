
#include "MyWindow.h"


const char* css_data = R"(
.hovered {
    background-color: @selected_bg_color;
}
)";

MyWindow::MyWindow(): top_panel(&this->files_space) {
    set_title("GTKmm App");
    set_default_size(800, 400);

    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(css_data);

    auto screen = Gdk::Screen::get_default();
    Gtk::StyleContext::add_provider_for_screen(
        screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);


    // === Left Panel (Side panel with buttons) ===
    vbox.set_spacing(10);
    vbox.pack_start(button1, Gtk::PACK_SHRINK);
    vbox.pack_start(button2, Gtk::PACK_SHRINK);
    vbox.pack_start(button3, Gtk::PACK_SHRINK);

    vbox.set_spacing(20); // Set spacing between buttons
    vbox.set_margin_top(20); // Add top margin to the VBox
    vbox.set_margin_bottom(20); // Add bottom margin to the VBox
    vbox.set_margin_start(10); // Add left margin to the VBox
    vbox.set_margin_end(10); // Add right margin to the VBox

    // Connect button signals
    button1.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button1_clicked));
    button2.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button2_clicked));
    button3.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button3_clicked));

    // Add VBox to a scrolled window (optional for better scrolling when the window is small)
    scroll_left.add(vbox);
    scroll_left.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

    // === Right Panel (Center panel with text) ===
    label.set_text("Welcome! Select a button to display text here.");
    label.set_padding(20, 20); // Add some padding around the text

    // Add label to scrolled window

    // === Main Vertical Box (vbox_top) ===
    vbox_top.set_spacing(10); // Set spacing between elements in vbox_top

    // Add the horizontal box (vbox2) at the top of the main container
    vbox_top.pack_start(top_panel, Gtk::PACK_SHRINK);

    // === Paned Widget (splitting left and right panels) ===
    hpaned.set_position(200); // Set initial size for the side panel
    hpaned.add1(scroll_left); // Add the left side panel to the first part of the paned
    auto f = fm.getFiles();
    files_space.update(f);
    hpaned.add2(files_space); // Add the right side panel to the second part of the paned

    // Add the vertical box (vbox_top) and paned to the main window
    vbox_top.pack_start(hpaned); // Add the paned below the top horizontal box

    add(vbox_top);

    show_all_children();
}

// Button click event handlers
void MyWindow::on_button1_clicked() {
    label.set_text("You clicked Button 1!");
}

void MyWindow::on_button2_clicked() {
    label.set_text("You clicked Button 2!");
}

void MyWindow::on_button3_clicked() {
    label.set_text("You clicked Button 3!");
}
