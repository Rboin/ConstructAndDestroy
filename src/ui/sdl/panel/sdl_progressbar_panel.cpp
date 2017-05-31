//
// Created by Jeroen on 5/19/2017.
//

#include <sdl/progressbar/sdl_progressbar_render_object.h>
#include "sdl_progressbar_panel.h"

SDLProgressBarPanel::SDLProgressBarPanel(SDL_ProgressbarRenderObject *r, float duration, SDLPanel* parent) : SDLPanel(r) {
    _target_duration = duration;
    _finished = false;
    _parent = parent;
}

void SDLProgressBarPanel::render(SDLRenderer *renderer, float d) {
    if (_finished) {
        return;
    }

    _elapsed_duration += d;

    if (_elapsed_duration < _target_duration) {
        if (SDL_ProgressbarRenderObject* rep = dynamic_cast<SDL_ProgressbarRenderObject*>(this->get_representation())) {
            rep->set_progress(_elapsed_duration / _target_duration);

            SDLPanel::render(renderer, d);
        }
    } else {
        _finished = true;
        _parent->remove_component(this);
    }
}