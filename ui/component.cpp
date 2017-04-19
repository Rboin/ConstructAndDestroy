//
// Created by robin on 4/19/17.
//

#include "component.h"

Component::Component(const unsigned int width, const unsigned int height) :
        _width(width),
        _height(height),
        _children(std::vector<Component *>()) {

    this->resize(_width, _height);
}

void Component::add_child(Component *c) {
    c->setParent(this);
    _children.push_back(c);
}
