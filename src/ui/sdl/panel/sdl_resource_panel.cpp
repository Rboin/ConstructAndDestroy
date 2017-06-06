//
// Created by Sander on 3-5-2017.
//
#include <string>
#include <sstream>
#include <entity/player_manager.h>
#include <entity/player.h>
#include "sdl_resource_panel.h"

SDLResourcePanel::SDLResourcePanel(SDL_RenderObject *r) : SDLPanel(r) {
}

SDLResourcePanel::~SDLResourcePanel() {
    clear_components();
}

void SDLResourcePanel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());

    representation->set_position(v.x - offset.x, 0);
    old_window_size = v;
    resize_children(v);
}
