//
// Created by robin on 4/25/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_SLOT_H
#define CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_SLOT_H

#include <sdl/sdl_ui_component.h>
#include "event/slot.h"
#include "event/event_types.h"

class SDL_MouseEventSlot : public Slot<sdl_mouse_event_data> {
public:
    SDL_MouseEventSlot();

    void on(sdl_mouse_event_data d) override;
};
#endif //CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_SLOT_H
