//
// Created by Stephan Schrijver on 1-5-2017.
//

#include <iostream>
#include "sdl_key_event_dispatcher.h"
#include "sdl_event_types.h"

SDL_KeyEventDispatcher *SDL_KeyEventDispatcher::_instance = nullptr;

SDL_KeyEventDispatcher::SDL_KeyEventDispatcher() : SDL_EventDispatcher<sdl_key_event_data>() {}

SDL_KeyEventDispatcher *SDL_KeyEventDispatcher::get_instance() {
    if (!_instance) {
        _instance = new SDL_KeyEventDispatcher();
    }
    return _instance;
}

void SDL_KeyEventDispatcher::dispatch(sdl_key_event_data d) {
    // Wait 100ms between key events to prevent that 1 tap will te
    // triggered twice (or more).
    if ( previous_event_time < d.timestamp -500 || previous_event_button != d.key) {
        for (std::map<SDL_UIComponent *, Slot<sdl_key_event_data> *>::iterator it = _registered_slots.begin();
             it != _registered_slots.end(); ++it) {
            (*it).second->on(d);
        }
        previous_event_time = d.timestamp;
        previous_event_button = d.key;
    }
}

SDL_KeyEventDispatcher::~SDL_KeyEventDispatcher() {
    _instance = nullptr;
}

