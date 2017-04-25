//
// Created by robin on 4/25/17.
//

#include "sdl_mouse_event_dispatcher.h"

SDL_MouseEventDispatcher* SDL_MouseEventDispatcher::INSTANCE = nullptr;

SDL_MouseEventDispatcher::SDL_MouseEventDispatcher() : SDL_EventDispatcher<mouse_event_data>() {}

SDL_MouseEventDispatcher *SDL_MouseEventDispatcher::get_instance() {
    if(!INSTANCE) {
        INSTANCE = new SDL_MouseEventDispatcher();
    }
    return INSTANCE;
}

void SDL_MouseEventDispatcher::dispatch(mouse_event_data d) {
    SDL_UIComponent *best_component = nullptr;
    Slot<mouse_event_data> *best_slot = nullptr;
    for (std::map<SDL_UIComponent *, Slot<mouse_event_data> *>::iterator it = _registered_slots.begin();
         it != _registered_slots.end(); ++it) {
        SDL_UIComponent *current_component = (*it).first;
        float current_distance = current_component->get_position()->distance(d.position);
        if (current_component->contains_point(d.position) &&
            (!best_slot || current_distance < best_component->get_position()->distance(d.position))) {
            best_component = current_component;
            best_slot = (*it).second;
        }
    }
    if (best_slot) {
        best_slot->on(d);
    }
}


