//
// Created by Jeroen on 5/19/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_PANEL_H

#include "sdl_panel.h"

class SDL_ProgressbarRenderObject;
class SDLPanel;

class SDLProgressBarPanel : public SDLPanel {
public:
    explicit SDLProgressBarPanel(SDL_ProgressbarRenderObject *);
    void set_progress(float progress);
};

#endif //CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_PANEL_H
