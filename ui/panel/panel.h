//
// Created by robin on 4/19/17.
//

#ifndef CONSTRUCT_AND_DESTROY_PANEL_H
#define CONSTRUCT_AND_DESTROY_PANEL_H

#include "component.h"

class Panel : public Component {
public:
    explicit Panel(vec2 &, vec2 &);
};


#endif //CONSTRUCT_AND_DESTROY_PANEL_H
