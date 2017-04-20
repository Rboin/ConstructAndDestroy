//
// Created by robin on 4/19/17.
//


#include <QtWidgets/QApplication>
#include "window/window.h"
#include "panel/world_panel.h"
#include "vector.h"

int main(int argc, char **argv) {
    QApplication application(argc, argv);

    vec2 window_size = {400, 400}, window_pos = {0, 0};
    Window window("Main Window", window_size, window_pos);

    vec2 panel_size = {400, 400}, panel_pos = {0, 0};
    WorldPanel panel(panel_size, panel_pos);
    window.add_child(&panel);
    window.show();
    return application.exec();
}