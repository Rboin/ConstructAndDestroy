//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_COMPONENT_H

#include <vector>
#include <QtWidgets>
#include "types.h"

class Component : public QWidget {
protected:
    std::vector<Component *> children;
    vec2 &size, &position;

public:
    explicit Component(vec2 &, vec2 &);
    void add_child(Component *);

};

#endif //CONSTRUCT_AND_DESTROY_COMPONENT_H
