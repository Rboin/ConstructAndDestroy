//
// Created by Stephan Schrijver on 1-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_KEY_EVENT_DISPATCHER_H
#define CONSTRUCT_AND_DESTROY_SDL_KEY_EVENT_DISPATCHER_H

#include "sdl_event_dispatcher.h"
#include "sdl_event_types.h"

class SDL_KeyEventDispatcher : public SDL_EventDispatcher<sdl_key_event_data> {
private:
    static SDL_KeyEventDispatcher *_instance;

    SDL_KeyEventDispatcher();

public:
    static SDL_KeyEventDispatcher *get_instance();

    ~SDL_KeyEventDispatcher();

    void dispatch(sdl_key_event_data d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_KEY_EVENT_DISPATCHER_H
