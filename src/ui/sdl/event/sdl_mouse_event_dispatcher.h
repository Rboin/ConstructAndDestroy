//
// Created by robin on 4/25/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_DISPATCHER_H
#define CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_DISPATCHER_H

#include "sdl_event_dispatcher.h"

class SDL_MouseEventDispatcher : public SDL_EventDispatcher<mouse_event_data> {
private:
    static SDL_MouseEventDispatcher *INSTANCE;
    SDL_MouseEventDispatcher();
public:

    static SDL_MouseEventDispatcher *get_instance();

    void dispatch(mouse_event_data d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_DISPATCHER_H
