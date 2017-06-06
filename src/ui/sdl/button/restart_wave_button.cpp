//
// Created by robin on 5/24/17.
//

#include "restart_wave_button.h"

RestartWaveButton::RestartWaveButton(SDL_RenderObject *r) : SDLButton(r){
}

void RestartWaveButton::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());
    representation->set_position(representation->get_position()->x, v.y - offset.y);
    old_window_size = v;
}

void RestartWaveButton::render(SDLRenderer *t, mat2 &mat21, float d) {
    SDL_UIComponent::render(t, mat21, d);
}
