//
// Created by robin on 6/3/17.
//

#include "sdl_resource_label.h"

SDLResourceLabel::SDLResourceLabel(SDL_RenderObject *r) : SDLPanel(r){
}

void SDLResourceLabel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());
    representation->set_position(v.x - offset.x, representation->get_position()->y);
    old_window_size = v;
    resize_children(v);
}
