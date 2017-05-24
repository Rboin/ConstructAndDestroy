//
// Created by robin on 5/24/17.
//

#include "wave_reset_handler.h"
#include "wave/wave_manager.h"

void WaveResetHandler::on(sdl_mouse_event_data d) {
    if(d.type == SDL_MOUSEBUTTONUP) {
        WaveManager *wm = WaveManager::get_instance();
        wm->reset();
    }
}
