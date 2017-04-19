//
// Created by robin on 4/19/17.
//

#include "window.h"
#include "vector.h"

Window::Window(const char *title, vec2 &size, vec2 &position) :
        Component(size, position),
        _title(title) {

    this->setWindowTitle(title);
}

void Window::paintEvent(QPaintEvent *event) {
}
