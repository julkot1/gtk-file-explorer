#include <gtkmm.h>

#include "FileManager.h"
#include "MyWindow.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

FileManager fm(fs::current_path());


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.sideandcenter");
    auto c = fm.getFiles();
    for (auto f : c) {
        std::cout << f.name << " " << f.type << std::endl;
    }
    MyWindow window;
    return app->run(window);
}
