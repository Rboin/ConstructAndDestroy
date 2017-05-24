//
// Created by robin on 5/24/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_RESET_HANDLER_H
#define CONSTRUCT_AND_DESTROY_WAVE_RESET_HANDLER_H

#include "sdl_mouse_event_slot.h"

class WaveResetHandler : public SDL_MouseEventSlot {
public:
    void on(sdl_mouse_event_data d) override;
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_RESET_HANDLER_H
