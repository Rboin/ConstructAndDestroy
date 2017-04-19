//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_COMPONENT_H

#include <vector>
#include <QtWidgets>

class Component : public QWidget {
private:
    std::vector<Component *> _children;
    unsigned int _width, _height;
public:
    Component(const unsigned int, const unsigned int);
    void add_child(Component *);

};

#endif //CONSTRUCT_AND_DESTROY_COMPONENT_H
