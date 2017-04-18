//
// Created by robin on 3/21/17.
//

#ifndef C_AND_D_PROJECT_KEY_HANDLER_H
#define C_AND_D_PROJECT_KEY_HANDLER_H

#include "event_handler.h"

class Graph;

struct key_event_data : public event_data<SDL_Keycode> {
};

class KeyHandler : public EventHandler<key_event_data> {
public:
    bool handle(key_event_data data) override;
};


#endif //C_AND_D_PROJECT_KEY_HANDLER_H
