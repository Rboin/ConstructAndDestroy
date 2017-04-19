//
// Created by robin on 4/19/17.
//

#include "component.h"
#include "vector.h"


Component::Component(vec2 &si, vec2 &pos) :
        size(si),
        position(pos),
        children(std::vector<Component *>()) {

    this->resize((int) size.x, (int) size.y);
}

void Component::add_child(Component *c) {
    children.push_back(c);
    c->setParent(this);
}
