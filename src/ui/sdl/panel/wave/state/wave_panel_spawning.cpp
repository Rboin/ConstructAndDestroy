//
// Created by robin on 5/17/17.
//

#include <sstream>
#include <iomanip>
#include "entity/player_manager.h"
#include "wave_panel_spawning.h"
#include "sdl/text/sdl_render_solid_text.h"
#include "wave/wave.h"
#include "state/state_machine.h"
#include "wave_panel_preparing.h"
#include "wave_panel_finished.h"

void WavePanelSpawning::enter(SDLWavePanel *) {
}

void WavePanelSpawning::execute(SDLWavePanel *panel) {
    if(panel->get_wave()->is_preparing()) {
        panel->get_state_machine()->change_state(new WavePanelPreparing());
    } else if(panel->get_wave()->is_finished()) {
        panel->get_state_machine()->change_state(new WavePanelFinished());
    }
    update_text(panel->get_wave(), (sdl_solid_text *) panel->get_representation()->get_data());
}

void WavePanelSpawning::exit(SDLWavePanel *) {
}

void WavePanelSpawning::update_text(Wave *wave, sdl_solid_text *data) {
    std::string wave_title = std::to_string(wave->get_current_wave()) + " of " + std::to_string(wave->get_wave_size());
    std::string complete = "Wave: " + wave_title + "\nStat Modifier: x" + update_stat_modifier(wave)
                           + "\nElapsed: " + update_wave_time(wave);
    data->text = complete;
}

std::string WavePanelSpawning::update_wave_time(Wave *wave) {
    int elapsed_ms = (int) wave->get_elapsed_time(),
        seconds = (elapsed_ms / 1000) % 60,
        minutes = (elapsed_ms / 60000) % 60;

    std::string tmp_seconds = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);
    std::string tmp_minutes = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
    return tmp_minutes + ":" + tmp_seconds;
}

std::string WavePanelSpawning::update_stat_modifier(Wave *wave) {
    float modifier = wave->get_stat_modifier();
    std::ostringstream tmp;
    tmp << std::setprecision(4) << modifier;
    return tmp.str();
}