//
// Created by robin on 5/23/17.
//

#include <iostream>
#include <wave/wave_manager.h>
#include "wave_panel_finished.h"
#include "sdl/text/sdl_render_solid_text.h"
#include "wave/wave.h"
#include "state/state_machine.h"
#include "wave_panel_preparing.h"

void WavePanelFinished::enter(SDLWavePanel *t) {
}

void WavePanelFinished::execute(SDLWavePanel *t) {
    if(!t->get_wave()->is_finished() || t->get_wave()->is_preparing()) {
        t->get_state_machine()->change_state(new WavePanelPreparing());
    }
    update_text(t->get_wave(), (sdl_solid_text *) t->get_representation()->get_data());
}

void WavePanelFinished::exit(SDLWavePanel *t) {
}

void WavePanelFinished::update_text(Wave *w, sdl_solid_text *s) {
    if(w->player_won()) {
        s->text = "You won!";
    } else {
        s->text = "You lost!";
    }
}
