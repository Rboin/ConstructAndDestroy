//
// Created by robin on 5/17/17.
//

#include "wave_panel_preparing.h"
#include "sdl/text/sdl_render_solid_text.h"
#include "wave/wave.h"
#include "state/state_machine.h"
#include "wave_panel_spawning.h"
#include "wave_panel_finished.h"

void WavePanelPreparing::enter(SDLWavePanel *) {}

void WavePanelPreparing::execute(SDLWavePanel *panel) {
    if(!panel->get_wave()->is_preparing()) {
        panel->get_state_machine()->change_state(new WavePanelSpawning());
    } else if(panel->get_wave()->is_finished()) {
        panel->get_state_machine()->change_state(new WavePanelFinished());
    }
    update_text(panel->get_wave(), (sdl_solid_text *) panel->get_representation()->get_data());
}

void WavePanelPreparing::exit(SDLWavePanel *) {}

void WavePanelPreparing::update_text(Wave *wave, sdl_solid_text *data) {
    std::string wave_title =
        "Wave: " + std::to_string(wave->get_current_wave()) + " of " + std::to_string(wave->get_wave_size());
    std::string complete = wave_title + "\nPreparing...\n" + "Time left: " + update_wave_time(wave);
    data->text = complete;
}

std::string WavePanelPreparing::update_wave_time(Wave *wave) {
    int elapsed_ms = (int) wave->get_preparation_time(),
        seconds = (elapsed_ms / 1000) % 60,
        minutes = (elapsed_ms / 60000) % 60;

    std::string tmp_seconds = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);
    std::string tmp_minutes = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
    return tmp_minutes + ":" + tmp_seconds;
}
