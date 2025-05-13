#include "MyWindow.h"

#include <iostream>

auto css_data = R"(
.hovered {
    background-color: @selected_bg_color;
}
.selected {
    background-color: @selected_bg_color;
}
)";
extern FileManager fm;

MyWindow::MyWindow() : top_panel(&this->files_space) {
    set_title("GTKmm App");
    set_default_size(1000, 800);

    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(css_data);
    auto screen = Gdk::Screen::get_default();
    Gtk::StyleContext::add_provider_for_screen(
        screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    signal_key_press_event().connect(sigc::mem_fun(*this, &MyWindow::on_button_press_event));
    signal_key_release_event().connect(sigc::mem_fun(*this, &MyWindow::on_button_release_event));

    // Left VBox (Buttons)
    vbox.set_spacing(20);
    vbox.set_margin_top(20);
    vbox.set_margin_bottom(20);
    vbox.set_margin_start(10);
    vbox.set_margin_end(10);

    vbox.pack_start(button1, Gtk::PACK_SHRINK);
    vbox.pack_start(button2, Gtk::PACK_SHRINK);
    vbox.pack_start(button3, Gtk::PACK_SHRINK);

    button1.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button1_clicked));
    button2.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button2_clicked));
    button3.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button3_clicked));

    // Scrollable left panel
    scroll_left.add(vbox);
    scroll_left.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

    // Label (could be used somewhere, not yet packed)
    label.set_text("Welcome! Select a button to display text here.");
    label.set_padding(20, 20);

    // Top container (e.g., for navigation or toolbar)
    vbox_top.set_spacing(10);
    vbox_top.pack_start(top_panel, Gtk::PACK_SHRINK);

    // === Paned Widget ===
    hpaned.set_position(200);
    hpaned.set_hexpand(true);
    hpaned.set_vexpand(true);

    // Add left panel to first pane
    hpaned.add1(scroll_left);

    // Update right panel
    auto f = fm.getFiles();
    files_space.update(f);

    // Make files_space scrollable
    Gtk::ScrolledWindow* scroll_files = Gtk::manage(new Gtk::ScrolledWindow());
    scroll_files->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scroll_files->add(files_space);
    scroll_files->set_hexpand(true);
    scroll_files->set_vexpand(true);

    files_space.set_hexpand(true);
    files_space.set_vexpand(true);

    // Add scrollable files_space to second pane
    hpaned.add2(*scroll_files);

    // Pack paned into top container
    vbox_top.pack_start(hpaned, Gtk::PACK_EXPAND_WIDGET);
    vbox_top.set_hexpand(true);
    vbox_top.set_vexpand(true);

    add(vbox_top);
    show_all_children();
}

void MyWindow::update_files() {
    this->top_panel.update();
}

// Button handlers
void MyWindow::on_button1_clicked() {
    label.set_text("You clicked Button 1!");
}

void MyWindow::on_button2_clicked() {
    label.set_text("You clicked Button 2!");
}

void MyWindow::on_button3_clicked() {
    label.set_text("You clicked Button 3!");
}

bool MyWindow::on_button_release_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Control_L) {}
        fm.selectMode = false;
    return true;

}
bool MyWindow::on_button_press_event(GdkEventKey *event) {
   if (event->keyval ==  GDK_KEY_Control_L)
        fm.selectMode = true;
    return true;
}


