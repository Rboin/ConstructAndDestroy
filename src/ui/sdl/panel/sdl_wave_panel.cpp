//
// Created by robin on 5/16/17.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include "sdl/text/sdl_render_solid_text.h"
#include "sdl_wave_panel.h"
#include "state/state_machine.h"
#include "wave/wave.h"
#include "wave/state/wave_start.h"

SDLWavePanel::SDLWavePanel(SDLRenderSolidText *r, Wave *wave) : SDLPanel(r) {
    _wave_machine = new StateMachine<Wave>(wave);
    _wave_machine->change_state(new WaveStart());

    _title = "Wave: ";
    _max_wave = std::to_string(_wave_machine->entity->get_wave_size());
}

void SDLWavePanel::render(SDLRenderer *renderer, float delta) {
    _wave_machine->entity->update(delta);
    _wave_machine->update();
    update_representation();
    representation->render(renderer);
}

void SDLWavePanel::update_representation() {
    update_stat_modifier();
    update_wave_time();

    _current_wave = std::to_string(_wave_machine->entity->get_current_wave());

    sdl_solid_text *data = (sdl_solid_text *) representation->get_data();
    std::string complete = _title + _current_wave + " of " + _max_wave + "\n" +
                           "Stat Modifier: x" + _modifier + "\n" +
                           "Elapsed: " + _wave_time;

    data->text = complete;
}

void SDLWavePanel::update_wave_time() {
    int elapsed_ms = (int) _wave_machine->entity->get_elapsed_time(),
        seconds = (elapsed_ms / 1000) % 60,
        minutes = (elapsed_ms / 60000) % 60;

    std::string tmp_seconds = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);
    std::string tmp_minutes = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
    _wave_time = tmp_minutes + ":" + tmp_seconds;
}

void SDLWavePanel::update_stat_modifier() {
    std::ostringstream tmp;
    tmp << std::setprecision(2) << _wave_machine->entity->get_stat_modifier();
    _modifier = tmp.str();
}
