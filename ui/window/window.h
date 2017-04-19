//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WINDOW_H
#define CONSTRUCT_AND_DESTROY_WINDOW_H

#include "component.h"

class Window : public Component {
protected:
    const char *_title;
public:
    explicit Window(const char *, vec2 &, vec2 &);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //CONSTRUCT_AND_DESTROY_WINDOW_H
