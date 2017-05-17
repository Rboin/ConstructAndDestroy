//
// Created by robin on 5/16/17.
//

#include <iostream>
#include "sdl_wave_panel.h"
#include "sdl/panel/wave/state/wave_panel_preparing.h"
#include "sdl/text/sdl_render_solid_text.h"
#include "state/state_machine.h"
#include "wave/wave.h"

SDLWavePanel::SDLWavePanel(SDLRenderSolidText *r, Wave *wave) : SDLPanel(r) {
    _wave = wave;
    _wave_panel_state_machine = new StateMachine<SDLWavePanel>(this);
    _wave_panel_state_machine->change_state(new WavePanelPreparing());

    _title = "Wave: ";
    _max_wave = std::to_string(_wave->get_wave_size());
}

void SDLWavePanel::render(SDLRenderer *renderer, float delta) {
    _wave->update(delta);
    _wave_panel_state_machine->update();
    representation->render(renderer);
}

Wave *SDLWavePanel::get_wave() {
    return _wave;
}

StateMachine<SDLWavePanel> *SDLWavePanel::get_state_machine() {
    return _wave_panel_state_machine;
}