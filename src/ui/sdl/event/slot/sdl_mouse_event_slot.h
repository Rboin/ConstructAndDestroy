//
// Created by robin on 4/25/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_SLOT_H
#define CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_SLOT_H

#include "event/slot.h"

class SDL_MouseEventSlot : public Slot<mouse_event_data> {
public:
    SDL_MouseEventSlot();
    void on(mouse_event_data) override;
};
#endif //CONSTRUCT_AND_DESTROY_SDL_MOUSE_EVENT_SLOT_H
