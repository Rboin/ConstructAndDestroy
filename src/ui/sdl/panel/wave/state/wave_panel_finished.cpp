//
// Created by robin on 5/23/17.
//

#include <iostream>
#include <entity/player.h>
#include "settings.h"
#include "sdl/text/sdl_render_solid_text.h"
#include "entity/player_manager.h"
#include "wave_panel_finished.h"

void WavePanelFinished::enter(SDLWavePanel *t) {
    std::cout << "Entering finished state" << std::endl;
}

void WavePanelFinished::execute(SDLWavePanel *t) {
    update_text(t->get_wave(), (sdl_solid_text *) t->get_representation()->get_data());
}

void WavePanelFinished::exit(SDLWavePanel *t) {
}

void WavePanelFinished::update_text(Wave *w, sdl_solid_text *s) {
    Player *p = PlayerManager::get_instance()->get_player(player_id);
    if(p->units.size() > 0 || p->buildings.size() > 0) {
        s->text = "You won!";
    } else if(p->units.size() == 0 && p->buildings.size() == 0) {
        s->text = "You lost!";
    }
}
