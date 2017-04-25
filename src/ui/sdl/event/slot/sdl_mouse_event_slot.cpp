//
// Created by robin on 4/25/17.
//

#include "sdl_mouse_event_slot.h"

SDL_MouseEventSlot::SDL_MouseEventSlot() : Slot<mouse_event_data>() {}

void SDL_MouseEventSlot::on(mouse_event_data d) {
    // Example on mouse event callback.
    // You can determine whether the event is a mouse-motion, button-down/up event
    // by checking the data parameter.
}

