//
// Created by robin on 4/25/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_EVENT_DISPATCHER_H
#define CONSTRUCT_AND_DESTROY_SDL_EVENT_DISPATCHER_H

#include "sdl/sdl_ui_component.h"
#include "event/event_dispatcher.h"

template<typename T>
class SDL_EventDispatcher : public EventDispatcher<SDL_UIComponent, T> {
public:
    SDL_EventDispatcher() : EventDispatcher<SDL_UIComponent, T>() {}

    virtual void dispatch(T) = 0;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_EVENT_DISPATCHER_H
