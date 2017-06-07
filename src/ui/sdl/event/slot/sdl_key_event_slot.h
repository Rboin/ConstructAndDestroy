//
// Created by Stephan Schrijver on 1-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_KEY_EVENT_SLOT_H
#define CONSTRUCT_AND_DESTROY_SDL_KEY_EVENT_SLOT_H

#include "sdl/sdl_ui_component.h"
#include "event/slot.h"
#include "event/event_types.h"

class SDL_KeyEventSlot : public Slot<sdl_key_event_data> {
private:
    int _building_index;
public:
    SDL_KeyEventSlot();

    void on(sdl_key_event_data d) override;
    void handle_tab(Player*  player);
};
#endif //CONSTRUCT_AND_DESTROY_SDL_KEY_EVENT_SLOT_H
