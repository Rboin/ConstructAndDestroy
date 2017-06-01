//
// Created by Jeroen on 5/19/2017.
//

#include <sdl/progressbar/sdl_progressbar_render_object.h>
#include "sdl_progressbar_panel.h"

SDLProgressBarPanel::SDLProgressBarPanel(SDL_ProgressbarRenderObject *r) : SDLPanel(r) {}

SDLProgressBarPanel::~SDLProgressBarPanel() {
    clear_components();
}