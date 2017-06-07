//
// Created by robin on 6/6/17.
//

#include "sdl_badge_panel.h"

SDLBadgePanel::SDLBadgePanel(SDL_RenderObject *r) : SDLPanel(r){
}

void SDLBadgePanel::resize(const vec2 &v) {
    vec2 current_offset = old_window_size - (*representation->get_position());
    old_window_size = v;
    vec2 new_pos = v - current_offset;
    representation->set_position(representation->get_position()->x, new_pos.y);
}
