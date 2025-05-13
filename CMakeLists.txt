cmake_minimum_required(VERSION 3.10)
project(gtk)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

add_executable(gtk main.cpp
        MyWindow.cpp
        MyWindow.h
        TopPanel.cpp
        TopPanel.h
        FileManager.cpp
        FileManager.h
        FilesSpace.cpp
        FilesSpace.h
        FileEntry.cpp
        FileEntry.h
        FilespaceContextMenu.cpp
        FilespaceContextMenu.h
        File.h)
target_link_libraries(gtk ${GTKMM_LIBRARIES})
