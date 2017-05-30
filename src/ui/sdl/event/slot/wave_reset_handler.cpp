//
// Created by robin on 5/24/17.
//

#include <SDL_events.h>
#include "wave_reset_handler.h"
#include "wave/wave_manager.h"
#include "sdl/event/sdl_event_types.h"


void WaveResetHandler::on(sdl_mouse_event_data d) {
    if(d.type == SDL_MOUSEBUTTONUP) {
        WaveManager *wm = WaveManager::get_instance();
        wm->reset();
    }
}
