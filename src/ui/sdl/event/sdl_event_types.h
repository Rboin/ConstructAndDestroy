//
// Created by robin on 4/27/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_EVENT_TYPE_H
#define CONSTRUCT_AND_DESTROY_SDL_EVENT_TYPE_H

#include "event/event_types.h"

class SDL_UIComponent;
struct sdl_mouse_event_data : public mouse_event_data<SDL_UIComponent> {
    sdl_mouse_event_data(uint32_t ty, uint32_t time, vec2 &pos) : mouse_event_data<SDL_UIComponent>(ty, time, pos) {

    }
};

#endif //CONSTRUCT_AND_DESTROY_SDL_EVENT_TYPE_H
