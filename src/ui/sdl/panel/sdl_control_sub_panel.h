//
// Created by robin on 6/3/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_CONTROL_SUB_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_CONTROL_SUB_PANEL_H

#include "sdl_panel.h"

class SDLControlSubPanel : public SDLPanel {
public:
    explicit SDLControlSubPanel(SDL_RenderObject *);

    void resize(const vec2 &) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_CONTROL_SUB_PANEL_H
