//
// Created by robin on 6/3/17.
//

#include "sdl_control_sub_panel.h"

SDLControlSubPanel::SDLControlSubPanel(SDL_RenderObject *r) : SDLPanel(r){
}

void SDLControlSubPanel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());
    representation->set_position(representation->get_position()->x, v.y - offset.y);
    old_window_size = v;
    resize_children(v);
}
