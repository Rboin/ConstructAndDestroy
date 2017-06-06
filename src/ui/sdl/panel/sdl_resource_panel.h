//
// Created by Sander on 3-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RESOURCE_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_RESOURCE_PANEL_H

#include "sdl_panel.h"


class SDLResourcePanel : public SDLPanel {
public:
    explicit SDLResourcePanel(SDL_RenderObject *);
    ~SDLResourcePanel();

    void resize(const vec2 &) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_RESOURCE_PANEL_H
